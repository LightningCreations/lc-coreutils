
add_executable(true src/true.c)

target_link_libraries(true PRIVATE lc-coreutils-version)

install(TARGETS true)

add_manual(true "Does nothing, succesfully" 1)
if(LCNIX_COREUTILS_RUNTESTS)
    add_test(NAME true
            COMMAND true)
endif()