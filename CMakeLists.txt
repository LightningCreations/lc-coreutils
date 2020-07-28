cmake_minimum_required(VERSION 3.15)
project(lc-coreutils C)




set(LCNIX_KNOWN_COREUTILS "echo;false;true;hashfile;nohup;mkdir;pwd;link;yes;dirname;basename;chmod")

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

include(GNUInstallDirs)

set(LCNIX_COREUTILS_VERSION 0.1)

add_compile_definitions(_POSIX_C_SOURCE=200809L)

message(STATUS "Building coreutils, version ${LCNIX_COREUTILS_VERSION}")

configure_file(version.h.in version.h)

option(LCNIX_COREUTILS_RUNTESTS "Enables tests of coreutils that support them" ON)

if(LCNIX_COREUTILS_RUNTESTS)
    enable_testing()
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