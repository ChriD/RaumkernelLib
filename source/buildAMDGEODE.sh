#!/bin/bash
make arch=AMDGEODE dbg=1 clean
make arch=AMDGEODE dbg=1
/bin/cp -rf libs/_tmpBuild/raumkernel.so libs/linux_AMDGEODE/raumkernel.so
make arch=AMDGEODE dbg=1 clean

