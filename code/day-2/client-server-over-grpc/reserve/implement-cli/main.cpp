#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include <CsGrpcClientFactory.hpp>

using namespace csgrpc;

static
void
ShowUsage();

static
int
GetVersion();

int
main(
	int argc,
	char* argv[]
) {
	int result = 0;
	if (argc < 2) {
		ShowUsage();
		result = 1;
	} else if (!strcmp(argv[1], "help")) {
		ShowUsage();
	} else if (!strcmp(argv[1], "version")) {
		result = GetVersion();
	} else {
		std::cerr << "Error: Unkonwn command - " << argv[1] << std::endl;
		ShowUsage();
		result = 1;
	}
	return result;
}

void
ShowUsage(
) {
	std::cout 	<< "Usage: csgrpc-cli <command> <options> <arguments>"
				<< std::endl
				<< "\tCommands:" << std::endl
				<< "\t\tversion" << std::endl
				<< "\t\thelp" << std::endl;
}

int
GetVersion(
) {
	int result = 0;
	try {
		std::unique_ptr<CsGrpcClientInterface> csGrpcClient =
			CsGrpcClientFactory::Build();
		std::unique_ptr<CsGrpcVersion> version = csGrpcClient->GetVersion();
		std::cout 	<< "Version: "
					<< version->GetMajorVersion()
					<< "."
					<< version->GetMinorVersion()
					<< std::endl;
	} catch (std::exception& e) {
		std::cerr 	<< "Error retrieving version: "
					<< e.what()
					<< std::endl;
		result = 1;
	}
	return result;
}

