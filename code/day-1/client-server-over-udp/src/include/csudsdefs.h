/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for
 * details.
 */

#define BAIL_ON_CSUDS_ERROR(err) \
    if ((err) != 0) { \
        goto error; \
    }

#define CSUDS_SAFE_FREE_MEMORY(pMem) \
    if (pMem) { \
        DtlsUtilsFreeMemory(pMem); \
        (pMem) = NULL; \
    }

#define CSUDS_SAFE_FREE_STRING(pStr) \
    if (pStr) { \
        DtlsUtilsFreeString(pStr); \
        (pStr) = NULL; \
    }

#define CSUDS_SAFE_LOCK_MUTEX(bLocked, pMtx) \
    if (!(bLocked) && (pMtx) != NULL) { \
        pthread_mutex_lock(pMtx); \
        (bLocked) = 1; \
    }

#define CSUDS_SAFE_UNLOCK_MUTEX(bLocked, pMtx) \
    if ((bLocked) && (pMtx) != NULL) { \
        pthread_mutex_unlock(pMtx); \
        (bLocked) = 0; \
    }

#define CSUDS_IS_NULL_OR_EMPTY_STRING(pStr) \
    (!(pStr) || !(*pStr))

#define CSUDS_VALIDATE_POINTER(pPtr) \
    if ((pPtr) == NULL) { \
        err = ERROR_CSUDS_SESSION_INVALID_PARAMETER; \
        BAIL_ON_CSUDS_ERROR(err); \
    }

#define CSUDS_VALIDATE_STRING(pStr) \
    if (CSUDS_IS_NULL_OR_EMPTY_STRING(pStr)) { \
        err = ERROR_CSUDS_SESSION_INVALID_PARAMETER; \
        BAIL_ON_CSUDS_ERROR(err); \
    }

#define CSUDS_VALIDATE_POSITIVE_INTEGER(positiveIntVal) \
    if ((positiveIntVal) < 0) { \
        err = ERROR_CSUDS_SESSION_INVALID_PARAMETER; \
        BAIL_ON_CSUDS_ERROR(err); \
    }
