#!/bin/bash

autoreconf -vif .. && \
../configure \
	--prefix=/usr/lib/msft/csuds \
	--enable-debug=yes \
	--localstatedir=/var

