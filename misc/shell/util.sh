#!/bin/bash

demos="0_cmake 1_snapshot"

echoerr() { echo "$@" 1>&2; }

ungracefulExit()
{
    echoerr
    echoerr ERROR!!
    exit 1
}