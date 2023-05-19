noinst_LTLIBRARIES = libsrv-utils.la

libsrv_utils_la_SOURCES = \
    FileSystemUtils.cpp \
    libmain.cpp \
    Logger.cpp

libsrv_utils_la_CPPFLAGS = \
    -I$(top_srcdir)/server/utils/include \
    -I$(top_srcdir)/include \
    @OPENSSL_INCLUDES@

libsrv_utils_la_LIBADD = \
    @UUID_LIBS@ \
    @PTHREAD_LIBS@

libsrv_utils_la_LDFLAGS = \
    @OPENSSL_LDFLAGS@

