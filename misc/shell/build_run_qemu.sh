#!/bin/bash
# This script is used to build and run a project in QEMU
# Usage: ./build_run_qemu.sh <project path>
thisPath=$(realpath "$0")
thisDirPath=$(dirname "$thisPath")
demoPath="$1"

thisPath=$(realpath "$0")
thisDirPath=$(dirname "$thisPath")
source "${thisDirPath}/util.sh"

${thisDirPath}/build.sh "${demoPath}"

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
${thisDirPath}/run_qemu.sh "${demoPath}/build/demo"