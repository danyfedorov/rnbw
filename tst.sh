#!/usr/bin/env bash

if [ "$1" != "" ] && [ "$1" != "-" ]; then _from=$1;  else _from=17;  fi
if [ "$2" != "" ] && [ "$2" != "-" ]; then _to=$2;    else _to=231;   fi
if [ "$3" != "" ] && [ "$3" != "-" ]; then _how=$3;   else _how=0;    fi
if [ "$4" != "" ] && [ "$4" != "-" ]; then _angle=$4; else _angle=60; fi
if [ "$5" != "" ] && [ "$5" != "-" ]; then _width=$5; else _width=5;  fi

echo ARGS USED:
printf "%6s|%6s|%6s|%6s|%6s\n" from to how angle width
printf "%6s|%6s|%6s|%6s|%6s\n" $_from $_to $_how $_angle $_width

./mkblk.sh | ./rnbw $_from $_to $_how $_angle $_width
