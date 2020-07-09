add_executable(nohup src.c)

target_compile_definitions(nohup PRIVATE _POSIX_SOURCE)

install(TARGETS nohup)