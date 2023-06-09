/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for
 * details.
 */

#ifndef __CSUDS_H__
#define __CSUDS_H__

#ifdef __cplusplus
extern "C" {
#endif

#define ERROR_CSUDS_INVALID_PARAMETER        7000001
#define ERROR_CSUDS_ACCESS_DENIED            7000005
#define ERROR_CSUDS_NO_MORE_MEMORY           7000012
#define ERROR_CSUDS_SSL_INIT_FAILED          7000020
#define ERROR_CSUDS_SSL_CTX_CREATE_FAILED    7000021
#define ERROR_CSUDS_INVALID_CERT_CHAIN_PATH  7000022
#define ERROR_CSUDS_INVALID_PRIVATE_KEY_PATH 7000023
#define ERROR_CSUDS_INVALID_PRIVATE_KEY      7000024
#define ERROR_CSUDS_EPOLL_CREATE_FAILED      7000025
#define ERROR_CSUDS_EPOLL_ADD_FAILED         7000026
#define ERROR_CSUDS_EPOLL_DEL_FAILED         7000027
#define ERROR_CSUDS_LISTEN_FAILED            7000028
#define ERROR_CSUDS_LISTEN_RETRY             7000029
#define ERROR_CSUDS_READ_FAILED              7000030
#define ERROR_CSUDS_SSL_ACCEPT_FAILED        7000031
#define ERROR_CSUDS_COOKIE_GEN_FAILED        7000032
#define ERROR_CSUDS_SSL_ADDR_ALLOC_FAILED    7000033
#define ERROR_CSUDS_INVALID_ADDR_FAMILY      7000034
#define ERROR_CSUDS_DUPLICATE_RULE           7000035
#define ERROR_CSUDS_NO_SUCH_RULE             7000036
#define ERROR_CSUDS_INVALID_CONTEXT_TYPE     7000037
#define ERROR_CSUDS_INVALID_IP_ADDRESS       7000038
#define ERROR_CSUDS_CONNECT_FAILED           7000039

#define CSUDS_SVC_PATH "/var/run/csuds/csuds_socket"

#ifdef __cplusplus
}
#endif

#endif /* __CSUDS_H__ */
