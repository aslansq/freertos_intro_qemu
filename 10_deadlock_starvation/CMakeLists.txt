cmake_minimum_required(VERSION 3.10)

set(prj demo)

include("${CMAKE_CURRENT_SOURCE_DIR}/0_base/misc/cmake/arm.cmake")
set(freertos_root "${CMAKE_CURRENT_SOURCE_DIR}/0_base/misc/FreeRTOS")
include("${CMAKE_CURRENT_SOURCE_DIR}/0_base/misc/cmake/common_demo.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/0_base/misc/cmake/freertos.cmake")

# Set the project name
project(${prj})

set(demo_src "")

if(DEMO_DEADLOCK_C)
    message(STATUS "demo_deadlock.c is going to be used")
    set(demo_src "demo_deadlock.c")
endif()

if(DEMO_STICK_PRIO_C)
    message(STATUS "demo_stick_prio.c is going to be used")
    set(demo_src "demo_stick_prio.c")
endif()

if(DEMO_CHAIR_C)
    message(STATUS "demo_chair.c is going to be used")
    set(demo_src "demo_chair.c")
endif()

if(DEMO_LIVELOCK_C)
    message(STATUS "demo_livelock.c is going to be used")
    set(demo_src "demo_livelock.c")
endif()

if(NOT demo_src)
    message(WARNING "No demo source file specified.")
    message(STATUS "demo_deadlock.c is going to be used")
    set(demo_src "demo_deadlock.c")
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
