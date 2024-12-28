#!/bin/bash

demos="\
2_blinky \
3_task_scheduling \
3_task_scheduling_challenge \
4_memory \
4_memory_challenge \
5_queue \
5_queue_challenge \
6_mutex \
6_mutex_challenge"

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

    demo_6_mutex_macros="\
    -DAPP_DEMO_RACE:BOOL=ON\
    -DAPP_DEMO_MUTEX:BOOL=ON\
    "

    demo="$1"
    if [ "${demo}" == "4_memory" ]
    then
        echo "${demo_4_memory_macros}"
    elif [ "${demo}" == "6_mutex" ]
    then
        echo "${demo_6_mutex_macros}"
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