#!/bin/bash
# This script is used to run a demoBin
# Usage: ./run_qemu.sh <demoBin binary file> <optional: debug>
demoBin="$1"
debug="$2"

thisPath=$(realpath "$0")
thisDirPath=$(dirname "$thisPath")
source "${thisDirPath}/util.sh"

if [ ! -f "$demoBin" ]
then
    echoerr "demoBin binary does not exist: $demoBin"
    ungracefulExit
fi

buildPath=$(dirname "${demoBin}")
logFile=${buildPath}/log.txt
errFile=${buildPath}/err.txt

debugFlags=""

if [ "$debug" == "debug" ]
then
    debugFlags="-s -S"
    echo QEMU_DEBUG_MODE
elif [ "$debug" == "" ]
then
    debugFlags=""
else
    echoerr "Invalid debug flag: $debug"
    ungracefulExit
fi

if [ -z ${FREERTOS_INTRO_QEMU_TERM} ]
then
echo CONNECT below serial port to see simulated hardware:
qemu-system-arm -machine mps2-an385 -cpu cortex-m3 -kernel "$demoBin" -monitor none -nographic -serial stdio -serial pty $debugFlags | tee ${logFile}
else
${FREERTOS_INTRO_QEMU_TERM} -- bash -c "${thisDirPath}/screen_hw.sh ${logFile}" > ${errFile} 2>&1
# somehow auto screen failed. do manually
if [ $? != 0 ]
then
    echo see ${errFile} why auto screen failed.
    echo CONNECT below serial port to see simulated hardware:
fi
qemu-system-arm -machine mps2-an385 -cpu cortex-m3 -kernel "$demoBin" -monitor none -nographic -serial stdio -serial pty $debugFlags | tee ${logFile}
fi