#!/bin/sh
build/polygon_decomp < "$1" > input.txt
build/visualize < input.txt
firefox image.html
