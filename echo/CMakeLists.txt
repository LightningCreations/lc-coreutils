message(STATUS "Coreutils: Building echo")
add_executable(echo src/echo.c)
install(TARGETS echo DESTINATION bin)