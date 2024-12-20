add_subdirectory(CMSIS)

file(GLOB misc_src "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

set(src ${src} ${misc_src} PARENT_SCOPE)
set(inc ${inc} PARENT_SCOPE)