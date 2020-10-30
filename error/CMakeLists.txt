
add_library(error STATIC error.c error.h)

target_include_directories(error PUBLIC ${CMAKE_CURRENT_SOURCE_DIRECTORY})
