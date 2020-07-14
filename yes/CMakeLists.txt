
add_executable(yes yes.c)

target_link_libraries(yes PRIVATE lc-coreutils-version)

add_subdirectory(tests)

install(TARGETS yes)