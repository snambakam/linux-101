#include <CsGrpcClientFactory.hpp>
#include "CsGrpcClient.hpp"

using namespace csgrpc;

std::unique_ptr<CsGrpcClientInterface>
CsGrpcClientFactory::Build(
) {
    return CsGrpcClient::Build();
}