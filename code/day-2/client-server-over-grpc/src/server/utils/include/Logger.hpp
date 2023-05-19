#pragma once

#include <memory>
#include <string>

typedef enum {
    CSGRPC_LOG_LEVEL_ERROR = 0,
    CSGRPC_LOG_LEVEL_WARNING,
    CSGRPC_LOG_LEVEL_INFO,
    CSGRPC_LOG_LEVEL_VERBOSE,
    CSGRPC_LOG_LEVEL_DEBUG
} CSGRPC_LOG_LEVEL;

#define CSGRPC_LOG_MESSAGE_MAXLEN 1024

#define CSGRPC_LOG_MESSAGE(logger, logLevel, fmt, ... ) \
    do { \
        if (logger) { \
            (logger)->log(logLevel, fmt, ##__VA_ARGS__ ); \
        } \
    } while(0)

#define CSGRPC_LOG_ERROR(logger, fmt, ... ) \
    CSGRPC_LOG_MESSAGE(logger, CSGRPC_LOG_LEVEL_ERROR, fmt, ##__VA_ARGS__ )
#define CSGRPC_LOG_WARNING(logger, fmt, ... ) \
    CSGRPC_LOG_MESSAGE(logger, CSGRPC_LOG_LEVEL_WARNING, fmt, ##__VA_ARGS__ )
#define CSGRPC_LOG_INFO(logger, fmt, ... ) \
    CSGRPC_LOG_MESSAGE(logger, CSGRPC_LOG_LEVEL_INFO, fmt, ##__VA_ARGS__ )
#define CSGRPC_LOG_VERBOSE(logger, fmt, ... ) \
    CSGRPC_LOG_MESSAGE(logger, CSGRPC_LOG_LEVEL_VERBOSE, fmt, ##__VA_ARGS__ )
#define CSGRPC_LOG_DEBUG(logger, fmt, ... ) \
    CSGRPC_LOG_MESSAGE( \
        logger, \
        CSGRPC_LOG_LEVEL_DEBUG, \
        fmt " [%s:%d]", \
        ##__VA_ARGS__, __FILE__, __LINE__ \
    )

namespace csgrpc {
    class Logger final {
        public:
            Logger();
            virtual ~Logger();

            void
            log(
                CSGRPC_LOG_LEVEL logLevel,
                const char* fmt,
                ...);

            static std::shared_ptr<Logger>
            Build() {
                static std::shared_ptr<Logger> logger(new Logger());
                return logger;
            }
    };
}
