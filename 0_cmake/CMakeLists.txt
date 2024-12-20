cmake_minimum_required(VERSION 3.10)

set(prj demo)
set(freertos_root "${CMAKE_SOURCE_DIR}/FreeRTOS/FreeRTOS")

# Set the project name
project(${prj})

add_subdirectory(misc)
add_subdirectory(CMSIS)
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

#message("-- Source files for ${prj}:")
## Print each source file on a new line
#foreach(file ${src})
#    message("\t${file}")
#endforeach()
#
#message("-- Include files for ${prj}:")
## Print each source file on a new line
#foreach(file ${inc})
#    message("\t${file}")
#endforeach()
