lib_LTLIBRARIES = libcsudsclient.la

libcsudsclient_la_SOURCES = \
    libmain.c

libcsudsclient_la_CPPFLAGS = \
    -I$(top_srcdir)/include \
    -I$(top_srcdir)/include/public

libcsudsclient_la_LIBADD = \
    @top_builddir@/utils/libcsudsutils.la \
    @PTHREAD_LIBS@

libcsudsclient_la_LDFLAGS = \
    -export-symbols @top_srcdir@/client/csudsclient.exp

