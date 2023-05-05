/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for
 * details.
 */

#include "includes.h"

static
uint32_t
CsUdsServerCreateListenerParams(
    csuds_listener_params_t** ppParams
);

static
void
CsUdsServerFreeListenerParams(
    csuds_listener_params_t* pParams
);

static
uint32_t
CsUdsServerCreatePeerParams(
    csuds_peer_params_t** ppParams,
    struct sockaddr_un* pClientAddr,
    socklen_t lenClientAddr
);

static
void
CsUdsServerFreePeerParams(
    csuds_peer_params_t* pParams
);

uint32_t
CsUdsServerCreateListenerContext(
    csuds_context_t** ppContext
) {
    uint32_t err = 0;
    csuds_context_t* pContext = NULL;

    err = CsUdsUtilsAllocateMemory((void**)&pContext, sizeof(*pContext));
    BAIL_ON_CSUDS_ERROR(err);

    err = CsUdsServerCreateListenerParams(
            &pContext->params.pListener
            );
    BAIL_ON_CSUDS_ERROR(err);

    *ppContext = pContext;

cleanup:
    return err;
error:
    if (pContext) {
        CsUdsServerFreeContext(pContext);
    }
    goto cleanup;
}

uint32_t
CsUdsServerCreatePeerContext(
    csuds_context_t** ppContext,
    CSUDS_CONTEXT_TYPE contextType,
    int fd,
    struct sockaddr_un* pClientAddr,
    socklen_t lenClientAddr
) {
    uint32_t err = 0;
    csuds_context_t* pContext = NULL;

    if (!(contextType == CSUDS_CONTEXT_TYPE_INCOMING ||
          contextType == CSUDS_CONTEXT_TYPE_OUTGOING)) {
        err = ERROR_CSUDS_INVALID_PARAMETER;
        BAIL_ON_CSUDS_ERROR(err);
    }

    err = CsUdsUtilsAllocateMemory((void**)&pContext, sizeof(*pContext));
    BAIL_ON_CSUDS_ERROR(err);

    pContext->type = contextType;

    err = CsUdsServerCreatePeerParams(
            &pContext->params.pPeer,
            pClientAddr,
            lenClientAddr);
    BAIL_ON_CSUDS_ERROR(err);

    pContext->fd = fd;

    *ppContext = pContext;
cleanup:
    return err;
error:
    if (pContext) {
        CsUdsServerFreeContext(pContext);
    }
    goto cleanup;
}

void
CsUdsServerFreeContext(
    csuds_context_t* pContext
) {
    if (pContext) {
        switch (pContext->type) {
            case CSUDS_CONTEXT_TYPE_LISTENER:
                CsUdsServerFreeListenerParams(pContext->params.pListener);
                break;
            case CSUDS_CONTEXT_TYPE_INCOMING:
            case CSUDS_CONTEXT_TYPE_OUTGOING:
                CsUdsServerFreePeerParams(pContext->params.pPeer);
                break;
            case CSUDS_CONTEXT_TYPE_UNKNOWN:
                break;
        }
        if (pContext->fd >= 0) {
            close(pContext->fd);
            pContext->fd = -1;
        }
        CsUdsUtilsFreeMemory(pContext);
    }
}

static
uint32_t
CsUdsServerCreateListenerParams(
    csuds_listener_params_t** ppParams
) {
    uint32_t err = 0;
    csuds_listener_params_t* pParams = NULL;

    err = CsUdsUtilsAllocateMemory((void**)&pParams, sizeof(*pParams));
    BAIL_ON_CSUDS_ERROR(err);

    err = pthread_mutex_init(&pParams->mutex, NULL);
    BAIL_ON_CSUDS_ERROR(err);

    pParams->pMutex = &pParams->mutex;

    memset(&pParams->srvAddr, 0, sizeof(pParams->srvAddr));

    /* 
     * TODO
     */

    *ppParams = pParams;

cleanup:
    return err;
error:
    if (pParams) {
        CsUdsServerFreeListenerParams(pParams);
    }
    goto cleanup;
}

static
uint32_t
CsUdsServerCreatePeerParams(
    csuds_peer_params_t** ppParams,
    struct sockaddr_un* pClientAddr,
    socklen_t lenClientAddr
) {
    uint32_t err = 0;
    csuds_peer_params_t* pParams = NULL;

    err = CsUdsUtilsAllocateMemory((void**)&pParams, sizeof(*pParams));
    BAIL_ON_CSUDS_ERROR(err);

    if (pClientAddr && lenClientAddr > 0) {
        memcpy(&pParams->clientAddr, pClientAddr, lenClientAddr);
        pParams->lenClientAddr = lenClientAddr;
    }

    *ppParams = pParams;

cleanup:
    return err;
error:
    if (pParams) {
        CsUdsServerFreePeerParams(pParams);
    }
    goto cleanup;
}

void
CsUdsServerFreeListenerParams(
    csuds_listener_params_t* pParams
) {
    if (pParams) {
        if (pParams->pMutex) {
            pthread_mutex_destroy(pParams->pMutex);
            pParams->pMutex = NULL;
        }
        CsUdsUtilsFreeMemory(pParams);
    }
}

void
CsUdsServerFreePeerParams(
    csuds_peer_params_t* pParams
) {
    if (pParams) {
        CsUdsUtilsFreeMemory(pParams);
    }
}

