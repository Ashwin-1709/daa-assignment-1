#!/bin/bash

# use this to build
if [[ "$1" != "docs" ]]; then
    cmake --build build
else
    cmake --build build --target doxygen
fi
