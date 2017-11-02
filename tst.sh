#!/usr/bin/env bash

# ./gentxt.sh | ./rnbw -p rgb -w 2 -a 30 -c from 33 to 158 and back including, from 33 to 55, from 55 to 200 and back including -p bgr -c from 55 to 33
./gentxt.sh | ./rnbw -p rgb -w 2 -a 30 -c '[33<->158], [33->55], [55<i>200] -p bgr -c [55->33]'
