cmake_minimum_required(VERSION 3.10)

set(prj demo)

include("${CMAKE_CURRENT_SOURCE_DIR}/0_base/misc/cmake/arm.cmake")
set(freertos_root "${CMAKE_CURRENT_SOURCE_DIR}/0_base/misc/FreeRTOS")
include("${CMAKE_CURRENT_SOURCE_DIR}/0_base/misc/cmake/common_demo.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/0_base/misc/cmake/freertos.cmake")

# Set the project name
project(${prj})

set(demo_src "")

if(DEMO_UNBOUNDED_C)
    message(STATUS "demo_unbounded.c is going to be used")
    set(demo_src "demo_unbounded.c")
endif()

if(DEMO_INHERITANCE_C)
    message(STATUS "demo_inheritance.c is going to be used")
    set(demo_src "demo_inheritance.c")
endif()

if(NOT demo_src)
    message(WARNING "No demo source file specified.")
    message(STATUS "demo_unbounded.c is going to be used")
    set(demo_src "demo_unbounded.c")
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
