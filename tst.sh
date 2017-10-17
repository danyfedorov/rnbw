#!/usr/bin/env bash

if [ "$1" != "" ] && [ "$1" != "-" ]; then _from=$1;  else _from=16;  fi
if [ "$2" != "" ] && [ "$2" != "-" ]; then _to=$2;    else _to=231;   fi
if [ "$3" != "" ] && [ "$3" != "-" ]; then _how=$3;   else _how=0;    fi
if [ "$4" != "" ] && [ "$4" != "-" ]; then _angle=$4; else _angle=60; fi

echo "ARGS USED: " $_from $_to $_how $_angle
./mkblk.sh | ./rnbw $_from $_to $_how $_angle
