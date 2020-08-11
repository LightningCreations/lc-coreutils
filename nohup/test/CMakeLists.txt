
add_definitions(-D_POSIX_C_SOURCE=200809L -D_XOPEN_SOURCE=500L)

add_executable(nohuptest nohuptest.c)
add_executable(nohuptest0 nohuptest0.c)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/nohup-test)

add_test(NAME nohup-test
        COMMAND nohuptest $<TARGET_FILE:nohup> $<TARGET_FILE:nohuptest0>
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/nohup-test
    )


