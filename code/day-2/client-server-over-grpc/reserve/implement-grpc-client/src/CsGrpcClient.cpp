#include <CsGrpcClient.hpp>
#include <csgrpcdefs.h>

#include <sstream>
#include <memory>

using namespace csgrpc;
using grpc::Status;
using grpc::ClientContext;

CsGrpcClient::CsGrpcClient(
    std::shared_ptr<grpc::Channel> channel
)
:   _stub(CsGrpc::NewStub(channel))
{
}

CsGrpcClient::~CsGrpcClient(
) {
}

std::unique_ptr<CsGrpcVersion>
CsGrpcClient::GetVersion(
) {
    GetVersionParams params;
    ClientContext context;
    CsGrpcVersionRpc reply;

    Status status = _stub->GetVersion(&context, params, &reply);
    if (!status.ok()) {
        std::ostringstream os;
        os << "Error (code: "
            << status.error_code()
            << ") - "
            << status.error_message();
        throw std::runtime_error(os.str());
    }
    return std::unique_ptr<CsGrpcVersion>(
        new CsGrpcVersion(reply.major(), reply.minor())
    );
}

std::unique_ptr<CsGrpcClient>
CsGrpcClient::Build(
) {
    return std::unique_ptr<CsGrpcClient>(
        new CsGrpcClient(
            grpc::CreateChannel(
                CSGRPC_ADDRESS,
                grpc::InsecureChannelCredentials()
            )
        )
    );
}
