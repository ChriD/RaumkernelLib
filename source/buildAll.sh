#!/bin/bash
./buildX86.sh
./buildX64.sh
./buildARMV7HF.sh
./buildARMV6.sh
./buildARMV5TE.sh
#
./buildX86_test.sh
./buildX64_test.sh
./buildARMV7HF_test.sh
./buildARMV6_test.sh
./buildARMV5TE_test.sh

