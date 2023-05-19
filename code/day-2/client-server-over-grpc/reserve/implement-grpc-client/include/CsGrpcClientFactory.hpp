#pragma once

#include <CsGrpcClientInterface.hpp>
#include <memory>

namespace csgrpc {
    class CsGrpcClientFactory final {
        public:
            static
            std::unique_ptr<csgrpc::CsGrpcClientInterface>
            Build();
    };
}