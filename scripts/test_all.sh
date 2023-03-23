#!/usr/bin/fish
for file in (fd . test_polygons -uu)
    echo "Testing $file"
    ./run.sh $file
end
