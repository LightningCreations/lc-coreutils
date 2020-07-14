
add_executable(pwd pwd.c)

target_link_libraries(pwd PRIVATE lc-coreutils-version)

install(TARGETS pwd)

add_subdirectory(tests)