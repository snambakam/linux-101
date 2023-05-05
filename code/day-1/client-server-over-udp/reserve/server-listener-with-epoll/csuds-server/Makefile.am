lib_LTLIBRARIES = libcsuds-server.la

libcsuds_server_la_SOURCES = \
    context.c \
    globals.c \
    libmain.c \
    listener.c \
    poller.c

libcsuds_server_la_CPPFLAGS = \
    -I$(top_srcdir)/include \
    -I$(top_srcdir)/include/public \
    -I$(top_srcdir)/server/include

libcsuds_server_la_LIBADD = \
    @top_builddir@/utils/libcsudsutils.la \
    @PTHREAD_LIBS@

libcsuds_server_la_LDFLAGS = \
    -export-symbols @top_srcdir@/server/csuds-server/csuds.exp

