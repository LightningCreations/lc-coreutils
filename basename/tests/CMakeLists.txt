
add_test(NAME basename-matches-prgname
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/basename-matches-prgname.sh $<TARGET_FILE:basename>)

        add_test(NAME basename-suffix
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/basename-suffix.sh $<TARGET_FILE:basename>)
        
add_test(NAME basename-doesnt-segfault
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/basename-doesnt-segfault.sh $<TARGET_FILE:basename>)

add_test(NAME basename-multi-doesnt-segfault
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/basename-multi-doesnt-segfault.sh $<TARGET_FILE:basename>)

add_test(NAME basename-zero-doesnt-segfault
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/basename-zero-doesnt-segfault.sh $<TARGET_FILE:basename>)

add_test(NAME basename-help-doesnt-segfault
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/basename-doesnt-segfault.sh $<TARGET_FILE:basename>)

add_test(NAME basename-version-doesnt-segfault
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/basename-doesnt-segfault.sh $<TARGET_FILE:basename>)