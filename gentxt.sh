#!/usr/bin/env bash

# settings
WIDTH=4
HEIGHT=5
EL="☻☺☹"

for ((i = 0; i < $WIDTH; i++)); do
    for ((j = 0; j < $HEIGHT; j++)); do
        printf $EL
    done
    echo
done
