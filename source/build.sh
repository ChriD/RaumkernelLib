#!/bin/bash
ARCH=$1
rm -rf build/libs/linux_$ARCH
mkdir -p build
mkdir -p build/libs/
mkdir -p build/libs/linux_$ARCH
make arch=$ARCH dbg=1 clean
make arch=$ARCH dbg=1
/bin/cp -rf build/libraumkernel.so build/libs/linux_$ARCH/libraumkernel.so
/bin/cp -rf build/libraumkernel.a build/libs/linux_$ARCH/libraumkernel.a
make arch=$ARCH dbg=1 clean

