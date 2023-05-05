/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for
 * details.
 */

typedef enum {
    CSUDS_CONTEXT_TYPE_UNKNOWN = 0,
    CSUDS_CONTEXT_TYPE_LISTENER,
    CSUDS_CONTEXT_TYPE_INCOMING,
    CSUDS_CONTEXT_TYPE_OUTGOING
} CSUDS_CONTEXT_TYPE;

typedef enum {
    CSUDS_SESSION_STATE_INITIAL = 0,
    CSUDS_SESSION_STATE_ACCEPTED,
    CSUDS_SESSION_STATE_READY,
    CSUDS_SESSION_STATE_FAILED
} CSUDS_SESSION_STATE;
