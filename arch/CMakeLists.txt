
message(STATUS "arch(1): System processor ${CMAKE_SYSTEM_PROCESSOR}")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/helper.h.in ${CMAKE_CURRENT_BINARY_DIR}/helper.h)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(arch arch.c)

add_subdirectory(tests)



add_manual(arch "Prints system architecture name" 1)

install(TARGETS arch)
