#!/bin/bash
make arch=X86 clean
make arch=X86
/bin/cp -rf libs/_tmpBuild/raumkernel.so libs/linux_x86/raumkernel.so
make arch=X86 clean
