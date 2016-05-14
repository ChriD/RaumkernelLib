#!/bin/bash
make arch=ARMV6 clean
make arch=ARMV6
/bin/cp -rf libs/_tmpBuild/raumkernel.so libs/linux_ARMV6/raumkernel.so
make arch=ARMV6 clean
