/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for
 * details.
 */

#ifndef __CSUDS_UTILS_H__
#define __CSUDS_UTILS_H__

#ifdef __cplusplus
extern "C" {
#endif

uint32_t
CsUdsUtilsInitialize(
    void
    );

uint32_t
CsUdsUtilsAllocateMemory(
    void** ppMemory,
    size_t size
);

void
CsUdsUtilsFreeMemory(
    void* pMemory
);

uint32_t
CsUdsUtilsAllocateString(
    char** ppDst,
    const char* pSrc
);

void
CsUdsUtilsFreeString(
    char* pStr
);

unsigned
CsUdsInterlockedIncrement(
    unsigned volatile* pDst
);

unsigned
CsUdsInterlockedDecrement(
    unsigned volatile* pDst
);

void
CsUdsUtilsFinalize(
    void
    );

#ifdef __cplusplus
}
#endif

#endif /* __CSUDS_UTILS_H__ */

