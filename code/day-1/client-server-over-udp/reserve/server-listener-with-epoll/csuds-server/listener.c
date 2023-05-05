/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for
 * details.
 */

#include "includes.h"

uint32_t
CsUdsServerStartListenerContext(
    csuds_context_t* pContext
) {
    uint32_t err = 0;
    uint8_t bLocked = 0;
    csuds_listener_params_t* pParams = NULL;
    int on = 1;

    CSUDS_VALIDATE_POINTER(pContext);
    if (pContext->type != CSUDS_CONTEXT_TYPE_LISTENER) {
        err = ERROR_CSUDS_INVALID_PARAMETER;
        BAIL_ON_CSUDS_ERROR(err);
    }
    pParams = pContext->params.pListener;
    CSUDS_SAFE_LOCK_MUTEX(bLocked, pParams->pMutex);

    pContext->fd = socket(
                    PF_UNIX,
                    SOCK_STREAM,
                    0);
    if (pContext->fd < 0) {
        err = errno; // TODO: Map error
        BAIL_ON_CSUDS_ERROR(err);
    }

    if (setsockopt(
            pContext->fd,
            SOL_SOCKET,
            SO_REUSEADDR,
            &on,
            sizeof(on))< 0) {
        err = errno;
        BAIL_ON_CSUDS_ERROR(err);
    }

    /*
     * TODO: Create folders for socket path
     */

    unlink(CSUDS_SVC_PATH);

    pParams->srvAddr.sun_family = AF_UNIX;
    snprintf(pParams->srvAddr.sun_path, sizeof(CSUDS_SVC_PATH), CSUDS_SVC_PATH);

    if (bind(pContext->fd,
             (const struct sockaddr*)&pParams->srvAddr,
             sizeof(pParams->srvAddr)) < 0) {
        err = errno; // TODO: Map error
        BAIL_ON_CSUDS_ERROR(err);
    }

    if (listen(pContext->fd, SOMAXCONN) < 0) {
        err = errno; // TODO: Map error
        BAIL_ON_CSUDS_ERROR(err);
    }

    err = CsUdsServerPollerAddContext(pContext);
    BAIL_ON_CSUDS_ERROR(err);

error:
    CSUDS_SAFE_UNLOCK_MUTEX(bLocked, pParams->pMutex);
    return err;
}

uint32_t
CsUdsServerStopListenerContext(
    csuds_context_t* pContext
) {
    uint32_t err = 0;
    uint8_t bLocked = 0;
    csuds_listener_params_t* pParams = NULL;

    CSUDS_VALIDATE_POINTER(pContext);
    if (pContext->type != CSUDS_CONTEXT_TYPE_LISTENER) {
        err = ERROR_CSUDS_INVALID_PARAMETER;
        BAIL_ON_CSUDS_ERROR(err);
    }
    pParams = pContext->params.pListener;
    CSUDS_SAFE_LOCK_MUTEX(bLocked, pParams->pMutex);

    if (pContext->fd >= 0) {
        close(pContext->fd);
        pContext->fd = -1;
    }
error:
    CSUDS_SAFE_UNLOCK_MUTEX(bLocked, pParams->pMutex);
    return err;
}

