/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for
 * details.
 */

#ifndef __CSUDS_CLIENT_H__
#define __CSUDS_CLIENT_H__

#include <csuds/csuds.h>

#ifdef __cplusplus
extern "C" {
#endif

uint32_t
CsUdsClientInitialize(
    void
);

void
CsUdsClientFinalize(
    void
);

#ifdef __cplusplus
}
#endif

#endif /* __CSUDS_CLIENT_H__ */
