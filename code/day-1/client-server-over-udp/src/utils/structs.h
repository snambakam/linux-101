/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for
 * details.
 */

typedef struct _csuds_utils_globals_t {
    pthread_mutex_t mutex;
    uint8_t sslInitialized;
} csuds_utils_globals_t;
