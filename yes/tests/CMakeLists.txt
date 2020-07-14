
#add_test(NAME yes-read-y
#        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/yes-read-y.sh $<TARGET_FILE:yes>
#        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME yes-read-string
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/yes-read-string.sh $<TARGET_FILE:yes>
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})