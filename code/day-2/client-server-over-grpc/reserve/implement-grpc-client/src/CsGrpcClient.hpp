#pragma once

#include <CsGrpcClientInterface.hpp>

#include <memory>

#include <grpc++/grpc++.h>
#include "CsGrpc.grpc.pb.h"

namespace csgrpc {
    class CsGrpcClient final : public CsGrpcClientInterface {
        public:
            virtual ~CsGrpcClient();

            virtual std::unique_ptr<CsGrpcVersion>
            GetVersion();

            static
            std::unique_ptr<CsGrpcClient>
            Build();

        private:
            CsGrpcClient(std::shared_ptr<grpc::Channel> channel);
            CsGrpcClient(const CsGrpcClient&) = delete;
            CsGrpcClient(CsGrpcClient&&) = delete;
            CsGrpcClient& operator=(CsGrpcClient&&) = delete;
            CsGrpcClient& operator=(const CsGrpcClient&) = delete;

            std::unique_ptr<CsGrpc::Stub> _stub;
    };
}
