#!/bin/bash
ARCH=$1
rm -rf build/linux_$ARCH
mkdir -p build
mkdir -p build/linux_$ARCH
make arch=$ARCH dbg=1 clean
make arch=$ARCH dbg=1
/bin/cp -rf build/raumkernel.so build/linux_$ARCH/raumkernel.so
/bin/cp -rf build/raumkernel.a build/linux_$ARCH/raumkernel.a
make arch=$ARCH dbg=1 clean

