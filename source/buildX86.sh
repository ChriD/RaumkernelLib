#!/bin/bash
mkdir -p libs/_tmpBuild
make arch=X86 dbg=1 clean
make arch=X86 dbg=1
/bin/cp -rf libs/_tmpBuild/raumkernel.so libs/linux_x86/raumkernel.so
make arch=X86 dbg=1 clean
