#! /bin/bash -e

autoheader
aclocal
autoconf
autoreconf -fvi
automake --add-missing
./configure --prefix=/tmp/usr --enable-ebtables --enable-pgsql --enable-roaming --enable-debug
make

