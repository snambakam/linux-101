noinst_LTLIBRARIES = libcsgrpcclient.la

libcsgrpcclient_la_SOURCES = \
    CsGrpc.grpc.pb.cc \
    CsGrpc.pb.cc \
    CsGrpcClient.cpp \
    CsGrpcClientFactory.cpp \
    libmain.cpp

libcsgrpcclient_la_CPPFLAGS = \
    -I$(top_srcdir)/client/include \
    -I$(top_srcdir)/include \
    @OPENSSL_INCLUDES@

libcsgrpcclient_la_LIBADD = \
    @GRPC_LIBS@ \
    @PROTOBUF_LIBS@ \
    @UUID_LIBS@ \
    @CRYPTO_LIBS@ \
    @PTHREAD_LIBS@

libcsgrpcclient_la_LDFLAGS = \
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
