add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/misc")

# Add all source files in the current directory
file(GLOB base_src "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

set(src ${src} ${base_src} PARENT_SCOPE)
set(inc ${inc} ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)