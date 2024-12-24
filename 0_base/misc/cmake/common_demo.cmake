set(freertos_demo_common_root "${freertos_root}/FreeRTOS/Demo/Common")

set(common_demo_dir ${freertos_demo_common_root}/Minimal)
set(common_demo_inc ${freertos_demo_common_root}/include)

set(common_demo_src
    ${common_demo_dir}/AbortDelay.c
    ${common_demo_dir}/BlockQ.c
    ${common_demo_dir}/blocktim.c
    ${common_demo_dir}/countsem.c
    ${common_demo_dir}/death.c
    ${common_demo_dir}/dynamic.c
    ${common_demo_dir}/EventGroupsDemo.c
    ${common_demo_dir}/GenQTest.c
    ${common_demo_dir}/integer.c
    ${common_demo_dir}/IntQueue.c
    ${common_demo_dir}/IntSemTest.c
    ${common_demo_dir}/MessageBufferAMP.c
    ${common_demo_dir}/MessageBufferDemo.c
    ${common_demo_dir}/PollQ.c
    ${common_demo_dir}/QPeek.c
    ${common_demo_dir}/QueueOverwrite.c
    ${common_demo_dir}/QueueSet.c
    ${common_demo_dir}/QueueSetPolling.c
    ${common_demo_dir}/recmutex.c
    ${common_demo_dir}/semtest.c
    ${common_demo_dir}/StaticAllocation.c
    ${common_demo_dir}/StreamBufferDemo.c
    ${common_demo_dir}/StreamBufferInterrupt.c
    ${common_demo_dir}/TaskNotify.c
    ${common_demo_dir}/TaskNotifyArray.c
    ${common_demo_dir}/TimerDemo.c
)

set(src ${src} ${common_demo_src})
set(inc ${inc} ${common_demo_inc})