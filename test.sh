#! /bin/bash

while true; do
    RND=$(head /dev/urandom | tr -dc A-Za-z0-9 | head -c"$RANDOM")
    REF=$(echo "$RND" | md5sum | head -c32)
    RES=$(echo "$RND" | ./ft_ssl md5 | head -c32)
    if [ "$1" == "-v" ]; then
        echo "REF: $REF; RES: $RES";
    fi;
    if [ "$REF" != "$RES" ]; then
        echo "$RND" > test.error.log;
        echo "Exited, error log in `test.error.log`"
        exit 1;
    fi;
    if [ "$1" != "-v" ]; then
        echo "Passed !"
    fi;
done;
