
add_executable(which which.c)

add_manual(which "Finds paths to executable programs" 1)

add_subdirectory(tests)

install(TARGETS which)