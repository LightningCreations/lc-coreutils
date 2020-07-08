

foreach(hashalias ${LCNIX_COREUTILS_KNOWN_HASHSUM_ALIASES})
    add_test(NAME test-${hashalias}-sums
            COMMAND hashfile --algorithm ${hashalias} -c ${hashalias}sums
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endforeach()