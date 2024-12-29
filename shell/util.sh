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
6_mutex_challenge \
7_semaphore \
7_semaphore_challenge"

getMacros()
{
    demo_4_memory_macros="\
    -DDEMO_1_C:BOOL=ON\
    -DDEMO_2_C:BOOL=ON\
    -DDEMO_3_C:BOOL=ON\
    -DDEMO_4_C:BOOL=ON\
    -DDEMO_5_C:BOOL=ON\
    -DDEMO_6_C:BOOL=ON\
    "

    demo_6_mutex_macros="\
    -DDEMO_RACE_C:BOOL=ON\
    -DDEMO_MUTEX_C:BOOL=ON\
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