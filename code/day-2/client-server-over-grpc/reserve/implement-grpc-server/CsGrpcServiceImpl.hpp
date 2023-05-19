#pragma once

#include "CsGrpc.grpc.pb.h"
#include "CsGrpc.pb.h"

#include <Logger.hpp>

namespace csgrpc {

class CsGrpcServiceImpl final : public CsGrpc::Service {
    public:
        CsGrpcServiceImpl();

        grpc::Status
        GetVersion(
            grpc::ServerContext* context,
            const GetVersionParams* request,
            CsGrpcVersionRpc* reply
        ) override;

    private:
        std::shared_ptr<Logger> _logger;
};

}
