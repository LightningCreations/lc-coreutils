
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/test-mkdir)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/test-mkdir-mode)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/test-mkdir-mode-long)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/test-mkdir-mode-suid)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/test-mkdir-parents)

add_test(NAME mkdir
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/test-mkdir.sh $<TARGET_FILE:mkdir>
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/test-mkdir)

add_test(NAME mkdir-mode
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/test-mkdir-mode.sh $<TARGET_FILE:mkdir>
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/test-mkdir-mode)

add_test(NAME mkdir-mode-long
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/test-mkdir-mode-long.sh $<TARGET_FILE:mkdir>
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/test-mkdir-mode-long)

add_test(NAME mkdir-mode-suid
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/test-mkdir-mode-suid.sh $<TARGET_FILE:mkdir>
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/test-mkdir-mode-suid)

add_test(NAME mkdir-parents
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/test-mkdir-parents.sh $<TARGET_FILE:mkdir>
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/test-mkdir-parents)