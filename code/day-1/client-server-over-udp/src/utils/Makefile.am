noinst_LTLIBRARIES = libcsudsutils.la

libcsudsutils_la_SOURCES = \
    atomic.c \
    globals.c \
    libmain.c \
    memory.c \
    strings.c

libcsudsutils_la_CPPFLAGS = \
    -I$(top_srcdir)/include \
    -I$(top_srcdir)/include/public

libcsudsutils_la_LIBADD = \
    @PTHREAD_LIBS@

