
add_executable(link link.c)

target_link_libraries(link PRIVATE lc-coreutils-version)

add_subdirectory(tests)

add_manual(link "Creates a link to a file using the link syscall" 1)