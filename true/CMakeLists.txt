
message(STATUS "Coreutils: Building true")
add_executable(true src/true.c)

install(TARGETS true DESTINATION bin)