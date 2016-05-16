#!/bin/bash
make arch=ARMV6 dbg=1 clean
make arch=ARMV6 dbg=1
/bin/cp -rf libs/_tmpBuild/raumkernel.so libs/linux_ARMV6/raumkernel.so
make arch=ARMV6 dbg=1 clean
