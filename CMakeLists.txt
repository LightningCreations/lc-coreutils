cmake_minimum_required(VERSION 3.15)
project(lc-coreutils C)

set(LCNIX_ENABLE_COREUTILS "echo;false;true;hashfile;nohup;mkdir" CACHE STRING "Selects the list of coreutils to build and install")

include(GNUInstallDirs)

set(LCNIX_COREUTILS_VERSION 0.1)

message(STATUS "Building coreutils, version ${LCNIX_COREUTILS_VERSION}")

configure_file(version.h.in version.h)

option(LCNIX_COREUTILS_RUNTESTS "Enables tests of coreutils that support them" ON)

if(LCNIX_COREUTILS_RUNTESTS)
    enable_testing()
endif()

include_directories(${CMAKE_CURRENT_BINARY_DIR})

foreach(coreutil ${LCNIX_ENABLE_COREUTILS})
    message(STATUS "LCNix Coreutils: Building ${coreutil}")
    add_subdirectory(${coreutil})
endforeach()