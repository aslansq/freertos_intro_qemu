#!/bin/bash

demos="2_blinky 3_task_scheduling 3_task_scheduling_challenge 4_memory"

getMacros()
{
    demo_4_memory_macros="\
    -DAPP_DEMO=1\
    -DAPP_DEMO=2\
    -DAPP_DEMO=3\
    -DAPP_DEMO=4\
    -DAPP_DEMO=5\
    -DAPP_DEMO=6\
    "

    demo="$1"
    if [ "${demo}" == "4_memory" ]
    then
        echo "${demo_4_memory_macros}"
    fi
}

echoerr() { echo "$@" 1>&2; }

ungracefulExit()
{
    echoerr
    echoerr ERROR!! $0
    exit 1
}

echoWTab()
{
    while IFS= read -r line; do
    echo -e "\t$line"
    done <<< "$@"
}