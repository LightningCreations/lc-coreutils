
add_executable(basename basename.c)

add_subdirectory(tests)

add_manual(basename "Gets the directory name given a path name" 1)

install(TARGETS basename)