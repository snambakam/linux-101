/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for
 *  details.
 */

#include "includes.h"

uint32_t
CsUdsClientInitialize(
    void
    ) {
    uint32_t err = 0;

    err = CsUdsUtilsInitialize();
    BAIL_ON_CSUDS_ERROR(err);

error:
    return err;
}

void
CsUdsClientFinalize(
    void
    ) {
    CsUdsUtilsFinalize();
}

