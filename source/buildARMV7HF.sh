#!/bin/bash
make arch=ARMV7HF clean
make arch=ARMV7HF
/bin/cp -rf libs/_tmpBuild/raumkernel.so libs/linux_ARMV7/raumkernel.so
make arch=ARMV7HF clean
