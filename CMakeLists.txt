cmake_minimum_required(VERSION 3.15)
project(lc-coreutils C)

set(LCNIX_ENABLE_COREUTILS "echo;false;true;hashfile" CACHE STRING "Selects the list of coreutils to build and install")

include(GNUInstallDirs)

option(LCNIX_COREUTILS_RUNTESTS "Enables tests of coreutils that support them" ON)

if(LCNIX_COREUTILS_RUNTESTS)
    enable_testing()
endif()

foreach(coreutil ${LCNIX_ENABLE_COREUTILS})
    message(STATUS "LCNix Coreutils: Building ${coreutil}")
    add_subdirectory(${coreutil})
endforeach()