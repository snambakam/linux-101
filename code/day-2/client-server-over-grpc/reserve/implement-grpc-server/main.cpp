#include <CsGrpcService.hpp>
#include <iostream>
#include <stdexcept>

int
main(
	int argc,
	char* argv[]
) {
	int err = 0;
	try {
		std::unique_ptr<csgrpc::CsGrpcService> svc = 
			csgrpc::CsGrpcService::Build();
		svc->Run();
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		err = 1;
	}
	return err;
}
