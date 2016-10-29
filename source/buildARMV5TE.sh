#!/bin/bash
mkdir -p libs/_tmpBuild
make arch=ARMV5TE dbg=1 clean
make arch=ARMV5TE dbg=1
/bin/cp -rf libs/_tmpBuild/raumkernel.so libs/linux_ARMV5/raumkernel.so
make arch=ARMV5TE dbg=1 clean

