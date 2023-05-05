/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for
 * details.
 */

typedef struct _csuds_listener_params_t {
    pthread_mutex_t  mutex;
    pthread_mutex_t* pMutex;
} csuds_listener_params_t;

typedef struct _csuds_peer_params_t {
    uint32_t remotePort;
    struct sockaddr_storage clientAddr;
    socklen_t lenClientAddr;
} csuds_peer_params_t;

typedef struct _csuds_context_t {
    CSUDS_CONTEXT_TYPE type;
    int fd;
    union {
        csuds_listener_params_t* pListener;
        csuds_peer_params_t* pPeer;
    } params;
} csuds_context_t;

typedef struct _csuds_poller_t {
    pthread_mutex_t  mutex;
    /**
     * @brief Primary File Descriptor used by ePoll
     *
     */
    int ePollFd;
    /**
     * @brief These file descriptors are used to wake up the ePoll thread that
     *        is waiting for events. This is used to terminate the ePoll loop.
     */
    int wakeFd[2];
    /**
     * @brief Worker thread performing the poll
     *
     */
    pthread_t  worker;
    pthread_t* pWorker;
} csuds_poller_t;

typedef struct _csuds_service_globals_t {
    pthread_mutex_t  mutex;
    /**
     * @brief Poller that waits on socket events
     *
     */
    csuds_poller_t *pPoller;
} csuds_service_globals_t;
