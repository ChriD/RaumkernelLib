#!/bin/bash
make arch=ARMV5TE clean
make arch=ARMV5TE
/bin/cp -rf libs/_tmpBuild/raumkernel.so libs/linux_ARMV5/raumkernel.so
make arch=ARMV5TE clean

