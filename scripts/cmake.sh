#!/bin/bash

# run this when adding / deleting files
cmake -DCMAKE_BUILD_TYPE=Debug -S . -B build -G Ninja
