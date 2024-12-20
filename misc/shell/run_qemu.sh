#!/bin/bash
# This script is used to run a demo
# Usage: ./run_qemu.sh <demo file>
demo="$1"

ungracefulExit()
{
    echoerr
    echoerr ERROR!!
    exit 1
}

if [ ! -f "$demo" ]
then
    echoerr "Demo file does not exist: $demo"
    ungracefulExit
fi

qemu-system-arm -machine mps2-an385 -cpu cortex-m3 -kernel "$demo" -monitor none -nographic -serial stdio -s -S