#!/bin/bash

export MAKE=gmake

autoreconf -vif .. && \
../configure \
	--prefix=/usr/lib/csgrpc \
	--enable-debug=yes \
	--with-ssl=/usr \
	--localstatedir=/var \
	--with-grpc=/usr \
	--with-grpc-cpp-plugin=/usr
