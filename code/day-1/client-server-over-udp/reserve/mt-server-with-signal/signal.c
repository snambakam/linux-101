/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for
 * details.
 */

#include "includes.h"

static
void
CsUdsServerSignalHandler(
    int signalId
);

uint32_t
CsUdsServerBlockSignals(
    void
) {
    uint32_t err = 0;
    sigset_t originalMask;
    sigset_t blockedMask;

    sigemptyset(&blockedMask);
    sigaddset(&blockedMask, SIGINT);
    sigaddset(&blockedMask, SIGTERM);
    sigaddset(&blockedMask, SIGHUP);
    sigaddset(&blockedMask, SIGQUIT);
    sigaddset(&blockedMask, SIGPIPE);

    err = pthread_sigmask(SIG_BLOCK, &blockedMask, &originalMask);
    BAIL_ON_CSUDS_ERROR(err);
error:
    return err;
}

uint32_t
CsUdsServerHandleSignals(
    void
) {
    uint32_t err = 0;
    struct sigaction action;
    sigset_t mask;
    int signalId;

    memset(&action, 0, sizeof(action));
    action.sa_handler = CsUdsServerSignalHandler;

    sigaction(SIGINT, &action, NULL);

    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);

    err = pthread_sigmask(SIG_UNBLOCK, &mask, NULL);
    BAIL_ON_CSUDS_ERROR(err);

    sigemptyset(&mask);
    sigaddset(&mask, SIGTERM);
    sigaddset(&mask, SIGQUIT);
    sigaddset(&mask, SIGHUP);
    sigaddset(&mask, SIGPIPE);

    do {
        sigwait(&mask, &signalId); /* wait for a signal */
        switch(signalId) {
            case SIGINT:
            case SIGQUIT:
            case SIGTERM:
            {
                goto error;
            }
            default:
                break;
        }
    } while (1);
error:
    return err;
}

static
void
CsUdsServerSignalHandler(
    int signalId
) {
    switch (signalId) {
        case SIGINT:
            raise(SIGTERM);
        default:
            break;
    }
}
