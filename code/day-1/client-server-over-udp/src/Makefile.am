ACLOCAL_AMFLAGS = -I m4

BUILDROOT = @abs_top_builddir@
STAGEROOT = $(BUILDROOT)/stage

SUBDIRS = \
    utils

.PHONY: package stage

stage:
	make -C $(BUILDROOT) DESTDIR=$(STAGEROOT) install

package: stage package-rpm

package-rpm:
	@echo "Building RPM Package"
	cd $(BUILDROOT)/build/package

clean-local:
	-rm -rf $(BUILDROOT)/stage
	-rm -rf $(BUILDROOT)/build/*.rpm

distclean-local:
	-rm -rf $(BUILDROOT)/utils
	-rm -rf $(BUILDROOT)/server
	-rm -rf $(BUILDROOT)/client
	-rm -rf $(BUILDROOT)/include
	-rm -rf $(BUILDROOT)/test
