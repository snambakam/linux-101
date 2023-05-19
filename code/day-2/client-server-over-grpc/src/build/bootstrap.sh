#!/bin/bash

DISTRO=`cat /etc/os-release | grep "^ID" | awk -F "=" '{print $2;}'`

case $DISTRO in
	"ubuntu")
		export MAKE=gmake
		;;
	*)
		;;
esac

autoreconf -vif .. && \
../configure \
	--prefix=/usr/lib/csgrpc \
	--enable-debug=yes \
	--with-ssl=/usr \
	--localstatedir=/var \
	--with-grpc=/usr \
	--with-grpc-cpp-plugin=/usr
