#!/bin/bash
# This script is used to build and run a project in QEMU
# Usage: ./build_run_qemu.sh <project path>
thisPath=$(realpath "$0")
thisDirPath=$(dirname "$thisPath")
prjPath="$1"

ungracefulExit()
{
    echoerr
    echoerr ERROR!!
    exit 1
}

${thisDirPath}/build.sh "${prjPath}"

if [ $? != 0 ]; then
    echoerr "compilation failure"
    ungracefulExit
fi

if [ ! -f "${prjPath}/build/demo" ]
then
    echoerr "demo executable not found"
    ungracefulExit
fi

echo 'QEMU_started'
${thisDirPath}/run_qemu.sh "${prjPath}/build/demo"