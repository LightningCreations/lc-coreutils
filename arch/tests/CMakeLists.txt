
add_test(NAME arch-test
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/arch.sh $<TARGET_FILE:arch> ${CMAKE_SYSTEM_PROCESSOR})
