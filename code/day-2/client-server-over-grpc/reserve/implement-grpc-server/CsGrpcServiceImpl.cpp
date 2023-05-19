#include "CsGrpcServiceImpl.hpp"
#include "UUIDGenerator.hpp"
#include <PathAssistant.hpp>
#include <FileSystemUtils.hpp>
#include <csgrpcdefs.h>

using namespace grpc;
using namespace csgrpc;

CsGrpcServiceImpl::CsGrpcServiceImpl()
:   _logger(Logger::Build())
{
}

Status
CsGrpcServiceImpl::GetVersion(
    ServerContext* context,
    const GetVersionParams* request,
    CsGrpcVersionRpc* reply
) {
    CSGRPC_LOG_DEBUG(_logger, "Received call to GetVersion");
    reply->set_major(1);
    reply->set_minor(0);
    return Status::OK;
}

