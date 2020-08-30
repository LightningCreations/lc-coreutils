
add_executable(mknod mknod.c)

target_link_libraries(mknod chmod-parse)

add_manual(mknod "Creates a special file with a particular name" 1)

install(TARGETS mknod)

add_subdirectory(tests)