
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/unlink-remove-file)

add_test(NAME unlink-remove-file
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/unlink-remove-file
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/unlink-remove-file.sh $<TARGET_FILE:unlink>)
