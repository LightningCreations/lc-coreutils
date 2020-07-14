
add_executable(yes yes.c)

target_link_libraries(yes PRIVATE lc-coreutils-version)

add_manual(yes "Says yes to everything" 1)
add_subdirectory(tests)

install(TARGETS yes)