#pragma once

#include <string>
#include <uuid/uuid.h>

namespace csgrpc {
    class UUIDGenerator final {
        public:
            static std::string GenerateUUID() {
                uuid_t value;
                char buffer[37];
                uuid_generate(value);
                uuid_unparse_lower(value, buffer);
                return std::string(buffer);
            }
    };
}
