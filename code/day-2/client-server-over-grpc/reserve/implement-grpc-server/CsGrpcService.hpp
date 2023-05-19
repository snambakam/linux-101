#pragma once

#include <grpc++/grpc++.h>

#include <memory>
#include <pthread.h>

namespace csgrpc {
    class CsGrpcService final {
        public:
            virtual ~CsGrpcService();

            void Run();

            static
            std::unique_ptr<CsGrpcService>
            Build() {
                return std::unique_ptr<CsGrpcService>(
                    new CsGrpcService()
                );
            }

        private:
            CsGrpcService();
            CsGrpcService(const CsGrpcService&) = delete;
            CsGrpcService(CsGrpcService&&) = delete;
            CsGrpcService& operator=(CsGrpcService&&) = delete;
            CsGrpcService& operator=(const CsGrpcService&) = delete;

            void BlockSignals();
            void HandleSignals();

            void StartGrpcWorker();
            static void* GrpcWorkerRoutine(void* pArg);
            void RunGrpcService();
            void StopGrpcService();
            void StopGrpcWorker();

            static void SignalHandler(int signalId);

            std::unique_ptr<grpc::Server> _grpcServer;

            pthread_t _grpcWorker;
            pthread_t* _pGrpcWorker;
    };
}