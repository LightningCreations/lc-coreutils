message(STATUS "Coreutils: Building false")
add_executable(false src/false.c)
install(TARGETS false DESTINATION bin)