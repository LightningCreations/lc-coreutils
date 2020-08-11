
add_executable(coreutils_install install.c)

target_link_libraries(coreutils_install chmod-parse)

set_target_properties(coreutils_install PROPERTIES OUTPUT_NAME install)
