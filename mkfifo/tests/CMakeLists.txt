
add_executable(mkfifo-read-0 mkfifo-read-0.c)

add_test(NAME mkfifo-test-rw
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/mkfifo-test-rw.sh mkfifo mkfifo-read-0
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME mkfifo-test-sanity
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/mkfifo-test-sanity.sh mkfifo mkfifo-read-0
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})