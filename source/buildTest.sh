#!/bin/bash
ARCH=$1
rm -rf build/testDyn
rm -rf build/testStat
rm -rf build/testDyn$ARCH
rm -rf build/testStat$ARCH
mkdir -p build
make arch=$ARCH dbg=1 clean -f makefile_test
make arch=$ARCH dbg=1 -f makefile_test
/bin/cp -rf build/testDyn build/testDyn$ARCH
/bin/cp -rf build/testStat build/testStat$ARCH
make arch=$ARCH dbg=1 clean -f makefile_test

