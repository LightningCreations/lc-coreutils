
add_library(chmod-parse STATIC chmod-parse.h chmod-parse.c)


add_subdirectory(tests)

install(TARGETS chmod-parse)
install(FILES chmod-parse.h TYPE INCLUDE)