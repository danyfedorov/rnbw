#!/usr/bin/env bash

if [ $# -eq 0 ]; then
    script_num=1
else
    script_num=$1
fi

script_name="script-$script_num.rnbw"
echo "Running $script_name"
if [ -f $script_name ]; then
    ./generate-text.sh | ../rnbw $(< $script_name)
else
    tput setaf 1
    echo "Threre is no $script_name file"
    tput sgr0
fi
