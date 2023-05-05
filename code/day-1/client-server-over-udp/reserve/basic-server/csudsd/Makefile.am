sbin_PROGRAMS = csudsd

csudsd_SOURCES = \
    main.c \
    service.c

csudsd_CPPFLAGS = \
    -I$(top_srcdir)/include \
    -I$(top_srcdir)/include/public \
    -I$(top_srcdir)/server/include

csudsd_LDADD = \
    $(top_builddir)/utils/libcsudsutils.la \
    $(top_builddir)/server/csuds-server/libcsuds-server.la \
    @DL_LIBS@

