sbin_PROGRAMS = csgrpcd

csgrpcd_SOURCES = \
	main.cpp

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

