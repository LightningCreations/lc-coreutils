cmake_minimum_required(VERSION 3.15)
project(lc-coreutils C)


set(LCNIX_KNOWN_COREUTILS echo;false;true;hashfile;nohup;mkdir;pwd;link;yes;dirname;basename;chmod;mkfifo;mknod;which;arch)

set(LCNIX_ENABLE_COREUTILS "all" CACHE STRING "Selects the list of coreutils to build and install")

if(LCNIX_ENABLE_COREUTILS STREQUAL "all")
    set(LCNIX_ENABLE_COREUTILS ${LCNIX_KNOWN_COREUTILS})
endif()

include(GNUInstallDirs)

if(TARGET help2man)
    set(HELP2MAN help2man)
else()
    find_program(HELP2MAN help2man HINTS /usr/bin /usr/local/bin)
endif()

function(add_manual prg description section)
    if(NOT TARGET ${prg})
        message(FATAL_ERROR "${prg} is not an executable target")
    endif()
    get_target_property(type ${prg} TYPE)
    if(NOT ${type} STREQUAL "EXECUTABLE")
        message(FATAL_ERROR "${prg} is not an executable target")
    endif()
    if(NOT LCNIX_COREUTILS_MAN_PAGES AND NOT ${HELP2MAN} STREQUAL "HELP2MAN-NOTFOUND")
        add_custom_command(
            OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${prg}.${section}
            COMMAND ${HELP2MAN} --section=${section}
                "--source=Lightning Creations"
                --output=${CMAKE_CURRENT_BINARY_DIR}/${prg}.${section}
                --no-info
                "--name=${description}"
                $<TARGET_FILE:${prg}>
            COMMENT "Building Manual in Section ${section} for lc-coreutils ${prg}"
            DEPENDS ${prg}
        )
        add_custom_target(man-page-${prg}
                ALL
                DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${prg}.${section})
        install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${prg}.${section}
                DESTINATION ${CMAKE_INSTALL_MANDIR}/man${section})
    endif()
endfunction()

option(LCNIX_COREUTILS_VALGRIND_TESTS "Runs Valgrind tests on coreutils that have them" OFF)

if(LCNIX_COREUTILS_VALGRIND_TESTS)
    message(CHECK_START "Checking for valgrind")
    find_program(VALGRIND valgrind HINTS /usr/bin /usr/local/bin)
    
    if(VALGRIND STREQUAL "VALGRIND-NOTFOUND")
        message(CHECK_FAIL "NOTFOUND")
        message(WARNING "Valgrind tests were requested but valgrind was not found")
        set(LCNIX_COREUTILS_VALGRIND_TESTS OFF)
    else()
        message(CHECK_PASS "${VALGRIND}")
    endif()
endif()

include(GNUInstallDirs)

set(LCNIX_COREUTILS_VERSION 0.1)

add_compile_definitions(_POSIX_C_SOURCE=200809L)

message(STATUS "Building coreutils, version ${LCNIX_COREUTILS_VERSION}")

configure_file(version.h.in version.h)

option(LCNIX_COREUTILS_RUNTESTS "Enables tests of coreutils that support them" ON)

if(LCNIX_COREUTILS_RUNTESTS)
    enable_testing()
endif()

set(LCNIX_COREUTILS_SANITIZE "" CACHE STRING "Enables Sanitizers on builds")

if(LCNIX_COREUTILS_SANITIZE)
    if(NOT _LCNIX_COREUTILS_TESTED_SANITIZERS STREQUAL LCNIX_COREUTILS_SANITIZE)
        try_compile(
            _LCNIX_TEST_SANITIZERS_RESULT
            ${CMAKE_CURRENT_BINARY_DIR}/sanitizers-test
            ${CMAKE_CURRENT_SOURCE_DIR}/try_compile.c
            COMPILE_DEFINITIONS "-fsanitize=${LCNIX_COREUTILS_SANITIZE}"
            LINK_OPTIONS "-fsanitize=${LCNIX_COREUTILS_SANITIZE}"
        )
        if(NOT _LCNIX_TEST_SANITIZERS_RESULT)
            message(FATAL_ERROR "Requested sanitizer ${LCNIX_COREUTILS_SANITIZE} did not compile")
        endif()
        set(_LCNIX_COREUTILS_TESTED_SANITIZERS ${LCNIX_COREUTILS_SANITIZE} CACHE INTERNAL "")
    endif()
    if(LCNIX_COREUTILS_VALGRIND_TESTS)
        message(WARNING "Valgrind tests may not operate correctly when built with sanitizers")
    endif()
    message(STATUS "Building with the sanitizer ${LCNIX_COREUTILS_SANITIZE}")
    add_compile_options("$<$<NOT:$<CONFIG:Release>>:-fsanitize=${LCNIX_COREUTILS_SANITIZE}>")
    add_link_options("$<$<NOT:$<CONFIG:Release>>:-fsanitize=${LCNIX_COREUTILS_SANITIZE}>")
endif()

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/chmod-parse)
add_subdirectory(chmod-parse)

add_library(lc-coreutils-version INTERFACE)

target_sources(lc-coreutils-version INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/version.h)

foreach(coreutil ${LCNIX_ENABLE_COREUTILS})
    message(STATUS "LCnix Coreutils: Building ${coreutil}")
    add_subdirectory(${coreutil})
endforeach()
