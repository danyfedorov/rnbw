#!/usr/bin/env bash

if [ $# -eq 0 ]; then
    SCRIPT_NUM=1
else
    SCRIPT_NUM=$1
fi

RNBW_HOME=$(git rev-parse --show-toplevel)
EXAMPLES_DIR=$RNBW_HOME/examples
SCRIPT_NAME=$EXAMPLES_DIR/script-$SCRIPT_NUM.rnbw

echo "Running $SCRIPT_NAME"

if [ -f $SCRIPT_NAME ]; then
    $EXAMPLES_DIR/generate-text.sh | $RNBW_HOME/rnbw $(< $SCRIPT_NAME)
else
    tput setaf 1
    echo "Threre is no $SCRIPT_NAME file"
    tput sgr0
fi
