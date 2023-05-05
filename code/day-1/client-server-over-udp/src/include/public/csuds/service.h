/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for
 * details.
 */

#ifndef __DTLS_SERVICE_H__
#define __DTLS_SERVICE_H__

#include <dtls/session.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DTLS_SESSION_AES_KEY_SIZE  (32)
#define DTLS_SESSION_HMAC_KEY_SIZE (48)

typedef struct _dtls_context_t dtls_context_t;

typedef struct _dtls_completion_info_t {
    unsigned char sessionReadAesKey[DTLS_SESSION_AES_KEY_SIZE];
    unsigned char sessionReadHmacKey[DTLS_SESSION_HMAC_KEY_SIZE];
    unsigned char sessionWriteAesKey[DTLS_SESSION_AES_KEY_SIZE];
    unsigned char sessionWriteHmacKey[DTLS_SESSION_HMAC_KEY_SIZE];
    uint32_t readSequence;
    uint32_t writeSequence;
} dtls_completion_info_t;

/**
 * @brief Completion Callback for DTLS Server/Listener
 */

typedef uint32_t (*pfn_dtls_server_completion_cb_t) (
    dtls_context_t* pDtlsContext,
    dtls_completion_info_t* pCompletionInfo
);

/**
 * @brief Initialization routine for the DTLS Server Component Library
 *
 * @return uint32_t Returns 0 upon Success
 */

uint32_t
DtlsServerInitialize(
    void
);

/**
 * @brief Creates a DTLS Server/Listener Context that listens on a given UDP
 *        port for incoming connections.
 *
 * @param ppContext DTLS Server context created
 * @param port UDP Port the DTLS server listens for connections
 * @param pfnDtlsServerCompletionCb Callback to report on successful completion
 * @return uint32_t Returns 0 upon success
 */

uint32_t
DtlsServerCreateListenerContext(
    dtls_context_t** ppContext,
    uint32_t port,
    const char* pszCertChainPath,
    const char* pszPrivateKeyPath,
    pfn_dtls_server_completion_cb_t pfnDtlsServerCompletionCb
);

/**
 * @brief Register DTLS session rule that defines the SSL Parameters to use with
 *        an incoming connection.
 *
 * @param pContext    DTLS Server/Listener context
 * @param pClientRule Client Rule (Remote IP Address)
 * @param pszCertChainPath Path to cert chain to use for connection
 * @param pszPrivateKeyPath Path to private key to use for connection
 * @return uint32_t   Returns 0 on success
 */

uint32_t
DtlsServerRegisterSessionRule(
    dtls_context_t* pContext,
    const char* pRemoteIP,
    const char* pszCertChainPath,
    const char* pszPrivateKeyPath,
    const char* pszSubjectName
);

/**
 * @brief Unregister DTLS Session rule
 *
 * @param pContext    DTLS Server/Listener context
 * @param pClientRule Client Rule (Remote IP Address)
 * @return uint32_t   Returns 0 on success
 */

uint32_t
DtlsServerUnregisterSessionRule(
    dtls_context_t* pContext,
    const char* pszRemoteIP
);

/**
 * @brief Starts actively listening on a DTLS Server/Listener context.
 *
 * @param pContext DTLS Server/Listener context
 * @return uint32_t Returns 0 on success
 */

uint32_t
DtlsServerStartListenerContext(
    dtls_context_t* pContext
);

/**
 * @brief Stops actively listening on a DTLS Server/Listener context.
 *
 * @param pContext DTLS Server/Listener context
 * @return uint32_t Returns 0 on success
 */

uint32_t
DtlsServerStopListenerContext(
    dtls_context_t* pContext
);

/**
 * @brief Creates a context to track a DTLS outgoing connection to a remote host
 *
 * @param pContext DTLS Server/Listener context
 * @param pRemoteIpAddress Remote IP Address to connect to
 * @param remoteUdpPort Remote UDP Port to connect to
 * @return uint32_t Returns 0 on success
 */

uint32_t
DtlsServerCreateClientContext(
    dtls_context_t** ppContext,
    const char* pszRemoteIP,
    uint32_t port,
    const char* pszCertChainPath,
    const char* pszPrivateKeyPath,
    pfn_dtls_server_completion_cb_t pfnCompletion
);

/**
 * @brief Releases the DTLS Server/Listener context
 *
 * @param pContext DTLS Server/Listener context
 */
void
DtlsServerFreeContext(
    dtls_context_t* pContext
);

/**
 * @brief Cleanup routine for the DTLS Server Component Library
 *
 */
void
DtlsServerFinalize(
    void
);

#ifdef __cplusplus
}
#endif

#endif /* __DTLS_SERVICE_H__ */
