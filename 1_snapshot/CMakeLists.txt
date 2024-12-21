cmake_minimum_required(VERSION 3.10)

set(prj demo)
set(freertos_source_root "${CMAKE_SOURCE_DIR}/misc/FreeRTOS_Source")
set(freertos_demo_common_root "${CMAKE_SOURCE_DIR}/misc/FreeRTOS_Demo_Common")

# Set the project name
project(${prj})

add_subdirectory(misc)
include(../misc/cmake/arm.cmake)
include(../misc/cmake/freertos.cmake)
include(../misc/cmake/common_demo.cmake)

# Add all source files in the current directory
file(GLOB app_src "${CMAKE_SOURCE_DIR}/*.c")

set(src ${src} ${app_src})
set(inc ${inc} ${CMAKE_SOURCE_DIR})

# Add the executable
add_executable(${prj} ${src})
# Include directories
target_include_directories(${prj} PUBLIC ${inc})

include(../misc/cmake/log.cmake)
