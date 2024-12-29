#!/bin/bash
# This script is used to build and run a project in QEMU
# Usage: ./rebuild_run_qemu.sh <project path> <optional: debug> <optional: -DXMACROX:BOOL=ON>
# Eaxmple: ./rebuild_run_qemu.sh ../3_task_scheduling
# Eaxmple: ./rebuild_run_qemu.sh ../3_task_scheduling debug
# Eaxmple: ./rebuild_run_qemu.sh ../4_memory debug -DDEMO_1_C:BOOL=ON
thisPath=$(realpath "$0")
thisDirPath=$(dirname "$thisPath")
demoPath="$1"
debug=""
macro=""

for arg in $@
do
    if [[ $arg == -D* ]]
    then
        macro="$arg"
    elif [[ $arg == debug ]]
    then
        debug=debug
    fi
done

thisPath=$(realpath "$0")
thisDirPath=$(dirname "$thisPath")
source "${thisDirPath}/util.sh"

${thisDirPath}/rebuild.sh ${demoPath} ${macro}

if [ $? != 0 ]; then
    echoerr "compilation failure"
    ungracefulExit
fi

if [ ! -f "${demoPath}/build/demo" ]
then
    echoerr "demo executable not found"
    ungracefulExit
fi

echo 'QEMU_started'
${thisDirPath}/run_qemu.sh "${demoPath}/build/demo" "${debug}"