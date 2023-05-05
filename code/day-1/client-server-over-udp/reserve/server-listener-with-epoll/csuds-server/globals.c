/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for
 * details.
 */

#include "includes.h"

static csuds_poller_t gCsUdsPoller = {
    .mutex = PTHREAD_MUTEX_INITIALIZER,
    .wakeFd = {-1, -1}
};

static csuds_service_globals_t csudsSvcGlobals = {
    .mutex = PTHREAD_MUTEX_INITIALIZER,
    .pPoller = &gCsUdsPoller
};
csuds_service_globals_t* gpCsUdsServiceGlobals = &csudsSvcGlobals;
