#include "CsGrpcService.hpp"
#include "CsGrpcServiceImpl.hpp"
#include <csgrpcdefs.h>
#include <cstring>
#include <sstream>
#include <signal.h>

using namespace csgrpc;
using namespace grpc;

CsGrpcService::CsGrpcService(
)
:   _pGrpcWorker(NULL)
{
}

CsGrpcService::~CsGrpcService() {
    StopGrpcWorker();
}

void
CsGrpcService::Run() {
    BlockSignals();

    StartGrpcWorker();

    HandleSignals();
}

void
CsGrpcService::BlockSignals() {
    sigset_t originalMask;
    sigset_t blockedMask;

    sigemptyset(&blockedMask);
    sigaddset(&blockedMask, SIGINT);
    sigaddset(&blockedMask, SIGTERM);
    sigaddset(&blockedMask, SIGHUP);
    sigaddset(&blockedMask, SIGQUIT);
    sigaddset(&blockedMask, SIGPIPE);

    int err = pthread_sigmask(SIG_BLOCK, &blockedMask, &originalMask);
    if (err != 0) {
        std::ostringstream os;
        os << "Error (code: "
            << err
            << ") when setting pthread_sigmask";
        throw std::runtime_error(os.str());
    }
}

void
CsGrpcService::HandleSignals() {
    struct sigaction action;
    sigset_t mask;
    int signalId;

    memset(&action, 0, sizeof(action));
    action.sa_handler = CsGrpcService::SignalHandler;

    sigaction(SIGINT, &action, NULL);

    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);

    int err = pthread_sigmask(SIG_UNBLOCK, &mask, NULL);
    if (err != 0) {
        std::ostringstream os;
        os << "Error (code: "
            << err
            << ") when setting pthread_sigmask";
        throw std::runtime_error(os.str());}

    sigemptyset(&mask);
    sigaddset(&mask, SIGTERM);
    sigaddset(&mask, SIGQUIT);
    sigaddset(&mask, SIGHUP);
    sigaddset(&mask, SIGPIPE);

    err = pthread_sigmask(SIG_BLOCK, &mask, NULL);
    if (err != 0) {
        std::ostringstream os;
        os << "Error (code: "
            << err
            << ") when setting pthread_sigmask";
        throw std::runtime_error(os.str());
    }

    bool bPoll = true;
    do {
        sigwait(&mask, &signalId); /* wait for a signal */
        switch(signalId) {
            case SIGINT:
            case SIGQUIT:
            case SIGTERM:
            {
                bPoll = false;
                break;
            }
            default:
                break;
        }
    } while (bPoll);
}

void
CsGrpcService::SignalHandler(
    int signalId
) {
    switch (signalId) {
        case SIGINT:
            raise(SIGTERM);
        default:
            break;
    }
}

void
CsGrpcService::StartGrpcWorker(
) {
    int err = pthread_create(
                &_grpcWorker,
                NULL,
                &CsGrpcService::GrpcWorkerRoutine,
                this);
    if (err != 0) {
        std::ostringstream os;
            os << "Error (code: "
            << err
            << ") on pthread_create";
            throw std::runtime_error(os.str());
    }
    _pGrpcWorker = &_grpcWorker;
}

void*
CsGrpcService::GrpcWorkerRoutine(
    void* pArg
) {
    CsGrpcService* pCsGrpc = static_cast<CsGrpcService*>(pArg);
    pCsGrpc->RunGrpcService();
    return NULL;
}

void
CsGrpcService::RunGrpcService(
) {
    std::string serverAddress(CSGRPC_ADDRESS);
    CsGrpcServiceImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(serverAddress, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    _grpcServer = builder.BuildAndStart();
    std::cout << "Server listening on " << serverAddress << std::endl;

    _grpcServer->Wait();
}

void
CsGrpcService::StopGrpcService(
) {
    if (_grpcServer) {
        _grpcServer->Shutdown();
    }
}

void
CsGrpcService::StopGrpcWorker(
) {
    if (_pGrpcWorker) {
        StopGrpcService();

        int err = pthread_join(_grpcWorker, NULL);
        if (err != 0) {
            std::ostringstream os;
            os << "Error (code: "
            << err
            << ") on pthread_join";
            throw std::runtime_error(os.str());
        }
        _pGrpcWorker = NULL;
    }
}