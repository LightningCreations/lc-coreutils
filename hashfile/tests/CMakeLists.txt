

foreach(hashalias ${LCNIX_COREUTILS_KNOWN_HASHSUM_ALIASES})
    add_test(NAME hashfile-${hashalias}-sums
            COMMAND hashfile --algorithm ${hashalias} -c ${hashalias}sums
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})


    if(LCNIX_COREUTILS_VALGRIND_TESTS)
        add_test(NAME valgrind-hashfile-${hashalias}-sums 
        COMMAND valgrind --error-exitcode=1 --exit-on-first-error=yes $<TARGET_FILE:hashfile> --algorithm ${hashalias} -c ${hashalias}sums
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )
    endif()
endforeach()