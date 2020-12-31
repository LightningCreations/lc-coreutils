file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/rmdir-single)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/rmdir-parents)

add_test(NAME rmdir-single 
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/rmdir-single
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/rmdir-single.sh $<TARGET_FILE:rmdir>)

add_test(NAME rmdir-parents 
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/rmdir-parents
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/rmdir-parents.sh $<TARGET_FILE:rmdir>)
