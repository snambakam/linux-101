/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for
 * details.
 */

#include "includes.h"

static csuds_utils_globals_t gCsUdsUtilsGlobals = {
    .mutex = PTHREAD_MUTEX_INITIALIZER,
    .sslInitialized = 0
};

csuds_utils_globals_t* pgCsUdsUtilsGlobals = &gCsUdsUtilsGlobals;
