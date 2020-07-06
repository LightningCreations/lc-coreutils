
add_executable(true src/true.c)

install(TARGETS true)

if(LCNIX_COREUTILS_RUNTESTS)
    add_test(NAME true
            COMMAND true)
endif()