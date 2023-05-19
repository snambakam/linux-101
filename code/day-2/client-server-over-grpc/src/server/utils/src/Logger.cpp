#include <Logger.hpp>
#include <iostream>
#include <stdarg.h>

using namespace csgrpc;

Logger::Logger() {
}

Logger::~Logger() {
}

void
Logger::log(
    CSGRPC_LOG_LEVEL logLevel,
    const char* fmt,
    ...
) {
    // TODO: Check log level
    char logMessage[CSGRPC_LOG_MESSAGE_MAXLEN+2] = {0};
    size_t lenLogMessage;
    va_list va;

    va_start(va, fmt);
    lenLogMessage = vsnprintf(logMessage, sizeof(logMessage)-2, fmt, va);
    logMessage[lenLogMessage+1] = '\n';
    logMessage[lenLogMessage+2] = '\0';

    std::cout << logMessage << std::endl;
}
