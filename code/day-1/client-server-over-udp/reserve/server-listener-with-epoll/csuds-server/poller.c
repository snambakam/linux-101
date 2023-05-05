/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for
 * details.
 */

#include "includes.h"

static
void*
CsUdsServerPollerExecute(
    void* pThrData
);

static
uint32_t
CsUdsServerProcessConnection(
    csuds_poller_t* pPoller,
    csuds_context_t* pContext
);

static
uint32_t
CsUdsServerAcceptConnection(
    csuds_context_t** ppContext,
    csuds_context_t* pContext
);

static
uint32_t
CsUdsServerReadConnection(
    csuds_context_t* pContext
);

uint32_t
CsUdsServerPollerInitialize(
    void
) {
    uint32_t err = 0;
    int iFd = 0;
    struct epoll_event epollEvent = {0};
    csuds_poller_t* pPoller = gpCsUdsServiceGlobals->pPoller;

    assert(pPoller != NULL);

    for (; iFd < sizeof(pPoller->wakeFd)/sizeof(pPoller->wakeFd[0]); iFd++) {
        pPoller->wakeFd[iFd] = -1;
    }

    if (pipe(pPoller->wakeFd) < 0) {
        err = errno; // TODO: Map Error
        BAIL_ON_CSUDS_ERROR(err);
    }

    pPoller->ePollFd = epoll_create1(EPOLL_CLOEXEC);
    if (pPoller->ePollFd < 0) {
         err = ERROR_CSUDS_EPOLL_CREATE_FAILED;
         BAIL_ON_CSUDS_ERROR(err);
    }

    /* Add the read fd of the wakeFd pipe to the ePoll events. When we need the
     * ePoll loop to terminate, we will write to the corresponding write fd
     */
    epollEvent.events = EPOLLIN | EPOLLET;
    epollEvent.data.fd = pPoller->wakeFd[0]; // read fd
    if (epoll_ctl(
            pPoller->ePollFd,
            EPOLL_CTL_ADD,
            pPoller->wakeFd[0],
            &epollEvent) < 0) {
        err = ERROR_CSUDS_EPOLL_ADD_FAILED;
        BAIL_ON_CSUDS_ERROR(err);
    }

    err = pthread_create(
            &pPoller->worker,
            NULL,
            &CsUdsServerPollerExecute,
            pPoller);
    BAIL_ON_CSUDS_ERROR(err);

    pPoller->pWorker = &pPoller->worker;

error:
    return err;
}

uint32_t
CsUdsServerPollerAddContext(
    csuds_context_t* pContext
) {
    uint32_t err = 0;
    csuds_poller_t* pPoller = gpCsUdsServiceGlobals->pPoller;
    struct epoll_event epollEvent = {0};
    uint8_t bLocked = 0;

    CSUDS_SAFE_LOCK_MUTEX(bLocked, &pPoller->mutex);
    epollEvent.events = EPOLLIN | EPOLLET;
    epollEvent.data.fd = pContext->fd;
    if (epoll_ctl(
            pPoller->ePollFd,
            EPOLL_CTL_ADD,
            pContext->fd,
            &epollEvent) < 0) {
        err = ERROR_CSUDS_EPOLL_ADD_FAILED;
        BAIL_ON_CSUDS_ERROR(err);
    }

error:
    CSUDS_SAFE_UNLOCK_MUTEX(bLocked, &pPoller->mutex);
    return err;
}

uint32_t
CsUdsServerPollerRemoveContext(
    csuds_context_t* pContext
) {
    uint32_t err = 0;
    csuds_poller_t* pPoller = gpCsUdsServiceGlobals->pPoller;
    struct epoll_event epollEvent = {0};
    uint8_t bLocked = 0;

    CSUDS_SAFE_LOCK_MUTEX(bLocked, &pPoller->mutex);
    epollEvent.events = EPOLLIN | EPOLLET;
    epollEvent.data.fd = pContext->fd;
    if (epoll_ctl(
            pPoller->ePollFd,
            EPOLL_CTL_DEL,
            pContext->fd,
            &epollEvent) < 0) {
        err = ERROR_CSUDS_EPOLL_DEL_FAILED;
        BAIL_ON_CSUDS_ERROR(err);
    }

error:
    CSUDS_SAFE_UNLOCK_MUTEX(bLocked, &pPoller->mutex);
    return err;
}

static
void*
CsUdsServerPollerExecute(
    void* pThrData
) {
    uint32_t err = 0;
    csuds_poller_t* pPoller = (csuds_poller_t*)pThrData;
    struct epoll_event epollEvents[64];

    assert (pPoller != NULL);

    do {
        int iEvent = 0;
        int nEvents = epoll_wait(
                        pPoller->ePollFd,
                        epollEvents,
                        sizeof(epollEvents)/sizeof(epollEvents[0]),
                        -1);
        if (nEvents < 0) {
            if (errno == EINTR) {
                continue;
            }
            err = errno;
            BAIL_ON_CSUDS_ERROR(err);
        }
        for (; iEvent < nEvents; iEvent++) {
            csuds_context_t* pContext = NULL;
            struct epoll_event* pEvent = &epollEvents[iEvent];
            if (pEvent->data.fd < 0) {
                /* Ignore invalid connection */
                continue;
            }
            if (pEvent->data.fd == pPoller->wakeFd[0]) {
                break;
            }

            pContext = (csuds_context_t*) pEvent->data.ptr;
            assert(pContext != NULL);

            err = CsUdsServerProcessConnection(pPoller, pContext);
            BAIL_ON_CSUDS_ERROR(err);
        }
    } while (1);

error:
    return NULL;
}

void
CsUdsServerPollerFinalize(
    void
) {
    csuds_poller_t* pPoller = gpCsUdsServiceGlobals->pPoller;
    if (pPoller) {
        int i = 0;
        if (pPoller->wakeFd[1] >= 0) {
            char buf[] = "\x04";
            ssize_t nWritten = write(pPoller->wakeFd[1], buf, sizeof(buf)-1);
            assert(nWritten == sizeof(buf)-1);
        }
        if (pPoller->pWorker) {
            pthread_join(*pPoller->pWorker, NULL);
            pPoller->pWorker = NULL;
        }
        /* Terminate ePoll loop */
        if (pPoller->ePollFd >= 0) {
            close(pPoller->ePollFd);
            pPoller->ePollFd = -1;
        }
        /* Close the file descriptors we use to wake up the ePoll loop to
         * facilitate termination
         */
        for (; i < sizeof(pPoller->wakeFd)/sizeof(pPoller->wakeFd[0]); i++) {
            if (pPoller->wakeFd[i] >= 0) {
                close(pPoller->wakeFd[i]);
                pPoller->wakeFd[i] = -1;
            }
        }
    }
}

static
uint32_t
CsUdsServerProcessConnection(
    csuds_poller_t* pPoller,
    csuds_context_t* pContext
) {
    uint32_t err = 0;
    struct epoll_event epollEvent = {0};
    csuds_context_t* pPeerContext = NULL;

    switch (pContext->type) {
        case CSUDS_CONTEXT_TYPE_LISTENER:
            /* Accept new connection */
            err = CsUdsServerAcceptConnection(&pPeerContext, pContext);
            switch (err) {
                case ERROR_CSUDS_LISTEN_FAILED:
                case ERROR_CSUDS_LISTEN_RETRY:
                    // TODO: Log error and continue
                    err = 0;
                    goto cleanup;
            }
            BAIL_ON_CSUDS_ERROR(err);
            // Add our new connection to our poll queue
            epollEvent.events = EPOLLIN | EPOLLET;
            epollEvent.data.fd = pPeerContext->fd;
            epollEvent.data.ptr = pPeerContext;
            if (epoll_ctl(
                    pPoller->ePollFd,
                    EPOLL_CTL_ADD,
                    pPeerContext->fd,
                    &epollEvent) < 0) {
                err = ERROR_CSUDS_EPOLL_ADD_FAILED;
                BAIL_ON_CSUDS_ERROR(err);
            }
            pPeerContext = NULL;
            break;
        case CSUDS_CONTEXT_TYPE_INCOMING:
        case CSUDS_CONTEXT_TYPE_OUTGOING:
        {
            err = CsUdsServerReadConnection(pContext);
            BAIL_ON_CSUDS_ERROR(err);
            break;
        }
        case CSUDS_CONTEXT_TYPE_UNKNOWN:
            err = ERROR_CSUDS_INVALID_CONTEXT_TYPE;
            BAIL_ON_CSUDS_ERROR(err);
            break;
    }
cleanup:
    return err;
error:
    if (pPeerContext) {
        CsUdsServerFreeContext(pPeerContext);
    }
    goto cleanup;
}

static
uint32_t
CsUdsServerAcceptConnection(
    csuds_context_t** ppContext,
    csuds_context_t* pContext
) {
    uint32_t err = 0;
    struct sockaddr_un clientAddr = {0};
    socklen_t address_length = 0;
    csuds_context_t* pPeerContext = NULL;
    int fd = -1;

    if (pContext->type != CSUDS_CONTEXT_TYPE_LISTENER) {
        err = ERROR_CSUDS_INVALID_PARAMETER;
        BAIL_ON_CSUDS_ERROR(err);
    }

    fd = accept(pContext->fd, (struct sockaddr*)&clientAddr, &address_length);
    if (fd < 0) {
        err = errno; // TODO: Map Error
        BAIL_ON_CSUDS_ERROR(err);
    }

    err = CsUdsServerCreatePeerContext(
            &pPeerContext,
            CSUDS_CONTEXT_TYPE_INCOMING,
            fd,
            &clientAddr,
            sizeof(clientAddr));
    BAIL_ON_CSUDS_ERROR(err);

    fd = -1;

    *ppContext = pPeerContext;
cleanup:
    if (fd >= 0) {
        close(fd);
    }
    return err;
error:
    if (pPeerContext) {
        CsUdsServerFreeContext(pPeerContext);
    }
    goto cleanup;
}

static
uint32_t
CsUdsServerReadConnection(
    csuds_context_t* pContext
) {
    uint32_t err = 0;

    if (!(pContext->type == CSUDS_CONTEXT_TYPE_INCOMING ||
          pContext->type == CSUDS_CONTEXT_TYPE_OUTGOING)) {
        err = ERROR_CSUDS_INVALID_PARAMETER;
        BAIL_ON_CSUDS_ERROR(err);
    }

    /*
     * TODO
     */

error:
    return err;
}
