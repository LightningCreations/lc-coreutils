add_executable(nohup src.c)

target_link_libraries(nohup PRIVATE lc-coreutils-version)

target_compile_definitions(nohup PRIVATE _POSIX_SOURCE)


if(LCNIX_COREUTILS_RUNTESTS)
    add_subdirectory(test)
endif()
install(TARGETS nohup)

add_manual(nohup "Runs a program, ignoring Hangup Signals" 1)

