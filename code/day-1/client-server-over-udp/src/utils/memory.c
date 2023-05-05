/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for
 * details.
 */

#include "includes.h"

uint32_t
CsUdsUtilsAllocateMemory(
    void** ppMemory,
    size_t size
) {
    uint32_t err = 0;
    void* pMemory = NULL;

    if (!ppMemory || size <= 0) {
        err = EINVAL;
        BAIL_ON_CSUDS_ERROR(err);
    }

    pMemory = calloc(1, size);
    if (!pMemory) {
        err = ENOMEM;
        BAIL_ON_CSUDS_ERROR(err);
    }

    *ppMemory = pMemory;
error:
    return err;
}

void
CsUdsUtilsFreeMemory(
    void* pMemory
) {
    if (pMemory) {
        free(pMemory);
    }
}
