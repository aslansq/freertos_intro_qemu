set(kernel_dir "${freertos_root}/FreeRTOS/Source/")

set(kernel_inc
    ${kernel_dir}/include
    ${kernel_dir}/portable/GCC/ARM_CM3
)

set(kernel_src
    ${kernel_dir}/tasks.c
    ${kernel_dir}/list.c
    ${kernel_dir}/queue.c
    ${kernel_dir}/timers.c
    ${kernel_dir}/event_groups.c
    ${kernel_dir}/stream_buffer.c
    ${kernel_dir}/portable/MemMang/heap_4.c
    ${kernel_dir}/portable/GCC/ARM_CM3/port.c
)

set(src ${src} ${kernel_src})
set(inc ${inc} ${kernel_inc})