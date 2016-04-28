#!/bin/bash
make arch=X64 clean
make arch=X64
/bin/cp -rf libs/_tmpBuild/raumkernel.so libs/linux_x64/raumkernel.so
make arch=X64 clean
