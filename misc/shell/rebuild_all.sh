#!/bin/bash

thisPath=$(realpath "$0")
thisDirPath=$(dirname "$thisPath")
source "${thisDirPath}/util.sh"
prjRootPath="${thisDirPath}/../.." # This is the root path of the project

demos="0_cmake 1_snapshot"

for demo in ${demos}
do
    echo "rebuilding ${demo}"
    echo "========================================"
    ${thisDirPath}/rebuild.sh "${prjRootPath}/${demo}"
    if [ $? != 0 ]
    then
        echoerr "build ${demo} failure"
        ungracefulExit
    else
        echo "build ${demo} success"
        echo "========================================"
    fi
done