
add_executable(link link.c)

target_link_libraries(link PRIVATE lc-coreutils-version)

add_subdirectory(tests)