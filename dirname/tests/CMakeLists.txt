
add_test(NAME dirname-matches-prgname
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/dirname-matches-prgname.sh $<TARGET_FILE:dirname> ${CMAKE_CURRENT_SOURCE_DIR})

add_test(NAME dirname-doesnt-segfault
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/dirname-doesnt-segfault.sh $<TARGET_FILE:dirname>)

add_test(NAME dirname-multi-doesnt-segfault
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/dirname-multi-doesnt-segfault.sh $<TARGET_FILE:dirname>)

add_test(NAME dirname-zero-doesnt-segfault
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/dirname-zero-doesnt-segfault.sh $<TARGET_FILE:dirname>)

add_test(NAME dirname-help-doesnt-segfault
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/dirname-doesnt-segfault.sh $<TARGET_FILE:dirname>)

add_test(NAME dirname-version-doesnt-segfault
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/dirname-doesnt-segfault.sh $<TARGET_FILE:dirname>)