/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for
 * details.
 */

// context.c

uint32_t
CsUdsServerCreateListenerContext(
    csuds_context_t** ppContext
);

uint32_t
CsUdsServerCreatePeerContext(
    csuds_context_t** ppContext,
    CSUDS_CONTEXT_TYPE contextType,
    int fd,
    struct sockaddr_un* pClientAddr,
    socklen_t lenClientAddr
);

void
CsUdsServerFreeContext(
    csuds_context_t* pContext
);

// poller.c

uint32_t
CsUdsServerPollerAddContext(
    csuds_context_t* pContext
);

uint32_t
CsUdsServerPollerRemoveContext(
    csuds_context_t* pContext
);

// service.c

uint32_t
CsUdsServerInitialize(
    void
);

void
CsUdsServerFinalize(
    void
);

