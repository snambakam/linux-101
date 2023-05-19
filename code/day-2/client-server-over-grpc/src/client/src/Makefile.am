noinst_LTLIBRARIES = libcsgrpcclient.la

libcsgrpcclient_la_SOURCES = \
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

