bin_PROGRAMS = csgrpc-cli

csgrpc_cli_SOURCES = \
	main.cpp

csgrpc_cli_CPPFLAGS = \
	-I$(top_srcdir)/client/include \
	-I$(top_srcdir)/include \
	@OPENSSL_INCLUDES@

csgrpc_cli_LDADD = \
	@top_builddir@/client/src/libcsgrpcclient.la \
	@UUID_LIBS@ \
	@CRYPTO_LIBS@ \
	@PTHREAD_LIBS@

csgrpc_cli_LDFLAGS = \
	@OPENSSL_LDFLAGS@
