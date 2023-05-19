sbin_PROGRAMS = csgrpcd

csgrpcd_SOURCES = \
	main.cpp \
	CsGrpcService.cpp \
	CsGrpcServiceImpl.cpp \
	CsGrpc.grpc.pb.cc \
	CsGrpc.pb.cc

csgrpcd_CPPFLAGS = \
	-I$(top_srcdir)/server/utils/include \
	-I$(top_srcdir)/include \
	@PROTOBUF_CFLAGS@ \
	@GRPC_CFLAGS@ \
	@OPENSSL_INCLUDES@

csgrpcd_LDADD = \
	@top_builddir@/server/utils/src/libsrv-utils.la \
	@PROTOBUF_LIBS@ \
	@GRPC_LIBS@ \
	@UUID_LIBS@ \
	@CRYPTO_LIBS@ \
	@PTHREAD_LIBS@

csgrpcd_LDFLAGS = \
	@OPENSSL_LDFLAGS@

CsGrpc.grpc.pb.cc: CsGrpc.pb.cc
	@PROTOC@ \
		-I @top_srcdir@/idl \
		--grpc_out=. \
		--plugin=protoc-gen-grpc=@GRPC_CPP_PLUGIN@ \
		@top_srcdir@/idl/CsGrpc.proto

CsGrpc.pb.cc:
	@PROTOC@ \
		-I @top_srcdir@/idl \
		--cpp_out=. \
		@top_srcdir@/idl/CsGrpc.proto

BUILT_SOURCES = \
	CsGrpc.grpc.pb.cc \
	CsGrpc.grpc.pb.h \
	CsGrpc.pb.cc \
	CsGrpc.pb.h

CLEANFILES = \
	CsGrpc.grpc.pb.cc \
	CsGrpc.grpc.pb.h \
	CsGrpc.pb.cc \
	CsGrpc.pb.h

