
enable_language(CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(LCNIX_COREUTILS_KNOWN_HASHSUM_ALIASES "md5;sha1;sha224;sha256;sha384;sha512")

set(LCNIX_COREUTILS_HASHSUM_ALIASES all CACHE STRING "Sets the list of aliases to hashsum to create. Note that omitting an alias will not disable support, support can be reobtained with hashfile --algorithm, or by creating the alias manually")

if("${LCNIX_COREUTILS_HASHSUM_ALIASES}" STREQUAL "all")
    set(LCNIX_COREUTILS_HASHSUM_ALIASES ${LCNIX_COREUTILS_KNOWN_HASHSUM_ALIASES})
endif()

add_executable(hashfile src/main.cpp src/sha2.c src/select_hash.h src/common.h src/hcommon.c src/md5.c)

install(TARGETS hashfile)

foreach(hashsum_alias ${LCNIX_COREUTILS_HASHSUM_ALIASES})
    list(FIND LCNIX_COREUTILS_KNOWN_HASHSUM_ALIASES ${hashsum_alias} idx)
    if(${idx} EQUAL -1)
        message(WARNING "Unknown alias for hashsum ${hashsum_alias}")
    else()
        message(STATUS "Creating hashsum alias ${hashsum_alias}")
        add_custom_command(TARGET hashfile POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E create_symlink hashfile ${CMAKE_CURRENT_BINARY_DIR}/${hashsum_alias}sum)
        install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/${hashsum_alias}sum TYPE BIN)
    endif()
endforeach()



if(LCNIX_COREUTILS_RUNTESTS)
    add_subdirectory(tests)
endif()