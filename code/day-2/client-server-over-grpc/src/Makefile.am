ACLOCAL_AMFLAGS = -I m4

SUBDIRS = \
	server \
	client/src \
	tools

clean-local:
	-rm -rf $(BUILDROOT)/stage
	-rm -rf $(BUILDROOT)/build/*.deb

distclean-local:
	-rm -rf $(BUILDROOT)/build
	-rm -rf $(BUILDROOT)/client
	-rm -rf $(BUILDROOT)/include
	-rm -rf $(BUILDROOT)/server
	-rm -rf $(BUILDROOT)/tools
	-rm -f @abs_top_srcdir@/aclocal.m4
	-rm -rf @abs_top_srcdir@/autom4te.cache
	-rm -f @abs_top_srcdir@/compile
	-rm -f @abs_top_srcdir@/config.guess
	-rm -f @abs_top_srcdir@/config.sub
	-rm -f @abs_top_srcdir@/configure
	-rm -f @abs_top_srcdir@/configure~
	-rm -f @abs_top_srcdir@/depcomp
	-rm -f @abs_top_srcdir@/install-sh
	-rm -f @abs_top_srcdir@/ltmain.sh
	-rm -rf @abs_top_srcdir@/m4/libtool.m4
	-rm -rf @abs_top_srcdir@/m4/lt~obsolete.m4
	-rm -rf @abs_top_srcdir@/m4/ltoptions.m4
	-rm -rf @abs_top_srcdir@/m4/ltsugar.m4
	-rm -rf @abs_top_srcdir@/m4/ltversion.m4
	-rm -f @abs_top_srcdir@/missing
	-rm -f @abs_top_srcdir@/ar-lib
	-rm -f `find @abs_top_srcdir@ -name Makefile.in`

