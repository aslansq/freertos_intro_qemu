#!/bin/bash

thisPath=$(realpath "$0")
thisDirPath=$(dirname "$thisPath")
source "${thisDirPath}/util.sh"
prjRootPath=$(realpath "${thisDirPath}/../..") # This is the root path of the project

for demo in ${demos}
do
    macros=$(getMacros "${demo}")
    if [ -z "$macros" ]
    then
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
    else
        for macro in ${macros}
        do
            echo "rebuilding ${demo} with ${macro}"
            echo "========================================"
            ${thisDirPath}/rebuild.sh ${prjRootPath}/${demo} ${macro}
            if [ $? != 0 ]
            then
                echoerr "build ${demo} with ${macro} failure"
                ungracefulExit
            else
                echo "build ${demo} with ${macro} success"
                echo "========================================"
            fi
        done
    fi
done

echo "All demos rebuilt successfully!"