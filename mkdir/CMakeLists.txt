
add_executable(mkdir mkdir.c)

target_link_libraries(mkdir PRIVATE chmod-parse lc-coreutils-version)

target_compile_definitions(mkdir PRIVATE -D_POSIX_C_SOURCE=200809L)
install(TARGETS mkdir)

add_subdirectory(tests)

add_manual(mkdir "Creates a new directory" 1)