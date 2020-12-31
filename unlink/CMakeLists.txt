
add_executable(unlink unlink.c)

add_manual(unlink "Unlinks the specified file" 1)

install(TARGETS unlink)

add_subdirectory(tests)
