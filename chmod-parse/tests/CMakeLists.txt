
set(_CHMOD_PARSE_TESTS 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19)

foreach(_parse_test ${_CHMOD_PARSE_TESTS})
    add_executable(chmod-parse-test${_parse_test} chmod-parse-test${_parse_test}.c)
    target_link_libraries(chmod-parse-test${_parse_test} chmod-parse)
    add_test(NAME chmod-parse-test${_parse_test}
            COMMAND chmod-parse-test${_parse_test})
    if(LCNIX_COREUTILS_VALGRIND_TESTS)
        add_test(NAME valgrind-chmod-parse-test${_parse_test}
                COMMAND ${VALGRIND} --error-exitcode=1 $<TARGET_FILE:chmod-parse-test${_parse_test}>)
    endif()
endforeach()