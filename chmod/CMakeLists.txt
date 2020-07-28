
add_executable(chmod chmod.c)

add_manual(chmod "Modifies the permissions of the target file" 1)

target_link_libraries(chmod PRIVATE chmod-parse lc-coreutils-version)

add_subdirectory(tests)

install(TARGETS chmod)