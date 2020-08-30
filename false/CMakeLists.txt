add_executable(false src/false.c)

target_link_libraries(false PRIVATE lc-coreutils-version)

install(TARGETS false)


add_test(NAME false
            COMMAND false)
set_property(TEST false PROPERTY WILL_FAIL ON)


add_manual(false "Does nothing, unsuccesfully" 1)