/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for
 * details.
 */

#include "includes.h"

int
main(int argc, char* argv[]) {
    uint32_t err = 0;
    /*
     * Block selected signals
     */
    err = CsUdsServerBlockSignals();
    BAIL_ON_CSUDS_ERROR(err);
    /*
     * Handle Service logic in separate thread which is blocked from selected
     * signals
     */
    err = CsUdsServerStart();
    BAIL_ON_CSUDS_ERROR(err);
    /*
     * Handle signals in main thread
     */
    err = CsUdsServerHandleSignals();
    BAIL_ON_CSUDS_ERROR(err);
error:
    CsUdsServerStop();
    return err;
}
