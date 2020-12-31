
add_executable(rmdir rmdir.c)

add_manual(rmdir "Removes a specified directory if it is empty" 1)

install(TARGETS rmdir)

add_subdirectory(tests)
