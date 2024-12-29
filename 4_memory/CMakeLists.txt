cmake_minimum_required(VERSION 3.10)

set(prj demo)

include("${CMAKE_CURRENT_SOURCE_DIR}/0_base/misc/cmake/arm.cmake")
set(freertos_root "${CMAKE_CURRENT_SOURCE_DIR}/0_base/misc/FreeRTOS")
include("${CMAKE_CURRENT_SOURCE_DIR}/0_base/misc/cmake/common_demo.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/0_base/misc/cmake/freertos.cmake")

# Set the project name
project(${prj})

set(demo_src "")

if(DEMO_1_C)
    message(STATUS "demo1.c is going to be used")
    set(demo_src "demo1.c")
endif()

if(DEMO_2_C)
    message(STATUS "demo2.c is going to be used")
    set(demo_src "demo2.c")
endif()

if(DEMO_3_C)
    message(STATUS "demo3.c is going to be used")
    set(demo_src "demo3.c")
endif()

if(DEMO_4_C)
    message(STATUS "demo4.c is going to be used")
    set(demo_src "demo4.c")
endif()

if(DEMO_5_C)
    message(STATUS "demo5.c is going to be used")
    set(demo_src "demo5.c")
endif()

if(DEMO_6_C)
    message(STATUS "demo6.c is going to be used")
    set(demo_src "demo6.c")
endif()

if(NOT demo_src)
    message(FATAL_ERROR "No demo source file specified. Please define one of the DEMO_X_C options.")
endif()

add_subdirectory(0_base)

# Add all source files in the current directory
set(demo_src "${CMAKE_CURRENT_SOURCE_DIR}/${demo_src}")

set(src ${src} ${demo_src})
set(inc ${inc} ${CMAKE_CURRENT_SOURCE_DIR})

# Add the executable
add_executable(${prj} ${src})
# Include directories
target_include_directories(${prj} PUBLIC ${inc})

include("${CMAKE_CURRENT_SOURCE_DIR}/0_base/misc/cmake/log.cmake")
