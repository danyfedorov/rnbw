#!/usr/bin/env bash

# settings
WIDTH=40
HEIGHT=50
EL="☻☺☹"

for ((i = 0; i < $WIDTH; i++)); do
    for ((j = 0; j < $HEIGHT; j++)); do
        printf $EL
    done
    echo
done
