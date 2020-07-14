add_executable(echo src/echo.c)

target_link_libraries(echo PRIVATE lc-coreutils-version)

install(TARGETS echo)