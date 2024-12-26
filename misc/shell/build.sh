#!/bin/bash
# This script is used to build a demo
# Usage: ./build.sh <demo path> <optional: macros>
demoPath=$(realpath "$1")
macros=""
if [ ! -z "$2" ]; then
    macros="$2"
fi

thisPath=$(realpath "$0")
thisDirPath=$(dirname "$thisPath")
source "${thisDirPath}/util.sh"

if [ -z "${demoPath}" ]
then
    echoerr "demo path is not provided"
    ungracefulExit
fi

if [ ! -d "${demoPath}" ]
then
    echoerr "demo path does not exist. ${demoPath}"
    ungracefulExit
fi

cd "${demoPath}"

if [ $? != 0 ]
then
    echoerr "cd ${demoPath} failure"
    ungracefulExit
fi

mkdir -p build
cd build
if [ ! -f build/Makefile ]
then
    echo cmake .. ${macros}
    cmake .. ${macros}
fi

make -j all