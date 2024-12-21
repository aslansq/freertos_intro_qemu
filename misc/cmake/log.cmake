file(WRITE "${CMAKE_BINARY_DIR}/source_files.txt" "")
# Print each source file to a file
foreach(file ${src})
    file(APPEND "${CMAKE_BINARY_DIR}/source_files.txt" "${file}\n")
endforeach()

file(WRITE "${CMAKE_BINARY_DIR}/include_files.txt" "")
# Print each include directory to a file
foreach(file ${inc})
    file(APPEND "${CMAKE_BINARY_DIR}/include_files.txt" "${file}\n")
endforeach()
