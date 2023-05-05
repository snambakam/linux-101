bin_PROGRAMS = csuds-cli

csuds_cli_SOURCES = \
    main.c

csuds_cli_CPPFLAGS = \
    -I$(top_srcdir)/include \
    -I$(top_srcdir)/include/public

csuds_cli_LDADD = \
    $(top_builddir)/utils/libcsudsutils.la \
    $(top_builddir)/client/libcsudsclient.la \
    @DL_LIBS@

