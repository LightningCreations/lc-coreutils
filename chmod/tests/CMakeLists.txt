
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/chmod-mode-correct)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/chmod-octal-correct)

add_test(NAME chmod-mode-correct
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/chmod-mode-correct.sh $<TARGET_FILE:chmod>
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/chmod-mode-correct)

add_test(NAME chmod-octal-correct
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/chmod-octal-correct.sh $<TARGET_FILE:chmod>
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/chmod-octal-correct)