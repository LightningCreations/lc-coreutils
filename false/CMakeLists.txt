add_executable(false src/false.c)

install(TARGETS false)

if(LCNIX_COREUTILS_RUNTESTS)
    add_test(NAME false
            COMMAND false)
    set_property(TEST false PROPERTY WILL_FAIL ON)
endif()