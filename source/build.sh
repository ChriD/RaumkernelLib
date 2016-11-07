#!/bin/bash
ARCH=$1
rm -rf build/linux_$ARCH/libs
mkdir -p build
mkdir -p build/linux_$ARCH
mkdir -p build/linux_$ARCH/libs
make arch=$ARCH dbg=1 clean
make arch=$ARCH dbg=1
/bin/cp -rf build/libraumkernel.so build/linux_$ARCH/libs/libraumkernel.so
/bin/cp -rf build/libraumkernel.a build/linux_$ARCH/libs/libraumkernel.a
make arch=$ARCH dbg=1 clean

