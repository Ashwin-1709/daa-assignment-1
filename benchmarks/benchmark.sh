#!/usr/bin/env bash

testcases=$(find test_polygons -type f | wc -l)

echo "$testcases"

pushd . > /dev/null
cd test_polygons

for testcase in $(find . -type f); do
    echo "$testcase"
    cat "$testcase"
    echo
done

popd > /dev/null
