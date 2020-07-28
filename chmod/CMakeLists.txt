
add_executable(chmod chmod.c)

target_link_libraries(chmod PRIVATE chmod-parse lc-coreutils-version)