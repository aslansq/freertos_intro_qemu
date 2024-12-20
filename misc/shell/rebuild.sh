#!/bin/bash
# This script is used to rebuild a project
# Usage: ./rebuild.sh <project path>
prjPath="$1"

thisPath=$(realpath "$0")
thisDirPath=$(dirname "$thisPath")
source "${thisDirPath}/util.sh"

if [ -z "${prjPath}" ]
then
    echoerr "project path is not provided"
    ungracefulExit
fi

if [ ! -d "${prjPath}" ]
then
    echoerr "project path does not exist"
    ungracefulExit
fi

rm -rf "${prjPath}/build"
"${thisDirPath}/build.sh" "${prjPath}"
