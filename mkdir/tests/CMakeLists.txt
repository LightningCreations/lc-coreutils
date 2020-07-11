
add_test(NAME mkdir
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/test-mkdir.sh $<TARGET_FILE:mkdir>
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME mkdir-mode
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/test-mkdir-mode.sh $<TARGET_FILE:mkdir>
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME mkdir-mode-long
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/test-mkdir-mode-long.sh $<TARGET_FILE:mkdir>
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME mkdir-mode-suid
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/test-mkdir-mode-suid.sh $<TARGET_FILE:mkdir>
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME mkdir-parents
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/test-mkdir-parents.sh $<TARGET_FILE:mkdir>
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})