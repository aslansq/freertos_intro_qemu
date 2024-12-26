#!/bin/bash
# This script is used to rebuild a demo
# Usage: ./rebuild.sh <demo path> <optional: macros>
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
    echoerr "demo path does not exist${demoPath}"
    ungracefulExit
fi

rm -rf "${demoPath}/build"
"${thisDirPath}/build.sh" ${demoPath} ${macros}
