#!/bin/bash
make arch=ARMV7HF dbg=1 clean
make arch=ARMV7HF dbg=1
/bin/cp -rf libs/_tmpBuild/raumkernel.so libs/linux_ARMV7/raumkernel.so
make arch=ARMV7HF dbg=1 clean
