
foreach(test mknod-creates-pipe mknod-mode mknod-mode-long mknod-mode-separated)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${test})
    add_test(
            NAME ${test}
            COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/${test}.sh $<TARGET_FILE:mknod>
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${test}
    )
endforeach()