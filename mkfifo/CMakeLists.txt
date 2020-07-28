
add_executable(mkfifo mkfifo.c)

target_link_libraries(mkfifo chmod-parse)

add_manual(mkfifo "Creates a fifo \\(named pipe\\) file" 1)

install(TARGETS mkfifo)
add_subdirectory(tests)