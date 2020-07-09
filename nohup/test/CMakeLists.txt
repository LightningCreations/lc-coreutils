
add_definitions(-D_POSIX_C_SOURCE=200809L)

add_executable(nohuptest nohuptest.c)
target_compile_options(nohuptest PRIVATE -pthread)
target_link_options(nohuptest PRIVATE -pthread)
add_executable(nohuptest0 nohuptest0.c)

