#pragma once

#include <CsGrpcVersion.hpp>
#include <memory>

namespace csgrpc {
    class CsGrpcClientInterface {
        public:

            virtual std::unique_ptr<CsGrpcVersion>
            GetVersion() = 0;
    };
}
