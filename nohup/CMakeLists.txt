add_executable(nohup src.c)

target_compile_definitions(nohup PRIVATE _POSIX_SOURCE)

if(LCNIX_COREUTILS_RUNTESTS)
#    add_subdirectory(test)
endif()
install(TARGETS nohup)

