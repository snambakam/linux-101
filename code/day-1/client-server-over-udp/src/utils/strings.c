/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for
 * details.
 */
#include "includes.h"

uint32_t
CsUdsUtilsAllocateString(
    char** ppDst,
    const char* pSrc
) {
    uint32_t err = 0;
    char* pDst = NULL;
    size_t len = 0;
    if (!pSrc) {
        err = ERROR_CSUDS_INVALID_PARAMETER;
        BAIL_ON_CSUDS_ERROR(err);
    }
    len = strlen(pSrc);
    pDst = calloc(1, len+1);
    if (!pDst) {
        err = ERROR_CSUDS_NO_MORE_MEMORY;
        BAIL_ON_CSUDS_ERROR(err);
    }
    memcpy(pDst, pSrc, len);

    *ppDst = pDst;
error:
    return err;
}

void
CsUdsUtilsFreeString(
    char* pStr
) {
    if (pStr) {
        free(pStr);
    }
}
