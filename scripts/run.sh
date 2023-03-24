#!/bin/sh
build/polygon_decomp < "$1" > input.txt
python3 ./utils/vis.py < input.txt
