#! /usr/bin/env bash

set -x

if [ "x$1" == "xclean" ]; then
    rm -rf build
    exit 0
fi

if [ ! -f build ]; then
    mkdir -p build
fi

cd ./build
cmake ..
make
cd ..
