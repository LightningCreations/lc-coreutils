
#file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/link-same-file)
#
#add_test(NAME link-same-file
#        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/link-same-file.sh $<TARGET_FILE:link>
#        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/link-same-file)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/link-same-content)

add_test(NAME link-same-content
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/link-same-content.sh $<TARGET_FILE:link>
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/link-same-content)

