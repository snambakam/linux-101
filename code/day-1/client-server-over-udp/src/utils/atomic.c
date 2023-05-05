/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for
 * details.
 */

#include "includes.h"

unsigned
CsUdsInterlockedIncrement(
    unsigned volatile* pDst
) {
    assert(pDst != NULL);
    return __sync_add_and_fetch(pDst, 1);
}

unsigned
CsUdsInterlockedDecrement(
    unsigned volatile* pDst
) {
    assert(pDst != NULL);
    return __sync_sub_and_fetch(pDst, 1);
}
