add_subdirectory(streamports/RingBuffer)
add_subdirectory(kernelports/FreeRTOS)

file(GLOB snapshot_trace_src "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

set(src
    ${src}
    ${snapshot_trace_src}
    PARENT_SCOPE)
set(inc
    ${inc}
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/config"
    PARENT_SCOPE
)