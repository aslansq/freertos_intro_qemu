#!/bin/bash
# This script is used to build a project
# Usage: ./build.sh <project path>
prjPath="$1"

ungracefulExit()
{
    echoerr
    echoerr ERROR!!
    exit 1
}

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

cd "${prjPath}"

if [ $? != 0 ]
then
    echoerr "cd ${prjPath} failure"
    ungracefulExit
fi

mkdir -p build
cd build
if [ ! -f build/Makefile ]
then
    cmake ..
fi

make -j all