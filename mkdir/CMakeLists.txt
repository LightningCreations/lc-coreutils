
add_executable(mkdir mkdir.c)

target_compile_definitions(mkdir PRIVATE -D_POSIX_C_SOURCE=200809L)
install(TARGETS mkdir)

add_subdirectory(tests)