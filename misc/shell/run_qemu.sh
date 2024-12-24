#!/bin/bash
# This script is used to run a demo
# Usage: ./run_qemu.sh <demo binary file> <optional: debug>
demo="$1"
debug="$2"

thisPath=$(realpath "$0")
thisDirPath=$(dirname "$thisPath")
source "${thisDirPath}/util.sh"

if [ ! -f "$demo" ]
then
    echoerr "Demo file does not exist: $demo"
    ungracefulExit
fi

debugFlags=""

if [ "$debug" == "debug" ]
then
    debugFlags="-s -S"
elif [ "$debug" == "" ]
then
    debugFlags=""
else
    echoerr "Invalid debug flag: $debug"
    ungracefulExit
fi

qemu-system-arm -machine mps2-an385 -cpu cortex-m3 -kernel "$demo" -monitor none -nographic -serial stdio $debugFlags