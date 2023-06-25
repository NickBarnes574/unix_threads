#!/bin/bash

# Args
DEBUG=0
TEST=0
CLEAN=0

# Arg parser
if [ $# -ne 0 ]; then
    if [[ $1 == "debug" ]]; then
        DEBUG=1
    elif [[ $1 == "test" ]]; then
        TEST=1
    elif [[ $1 == "clean" ]]; then
        rm -rf build
        rm -rf 1_Threads/bin
        exit 0
    else
        echo "USAGE: ./build.sh [ debug | test | clean ]" && \
            exit 1
    fi
fi

# Compile according to arg flags
mkdir -p build
cd build
set -e # Allows cicd pipline to report error
cmake .. -DCMAKE_BUILD_TYPE=${1}
make -j$(nproc)
(( TEST )) && ctest --output-on-failure

# Return to project root dir
cd ..
