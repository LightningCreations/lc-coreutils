# LC-Coreutils 

A reimplementation of the GNU Coreutils by Lightning Creations. 
The LC-Coreutils provide various utility programs for use on linux and other POSIX operating systems. 

The following coreutils are implemented and tested:
* true
* false
* echo
* mkdir
* nohup
* pwd
* md5sum, sha1sum, sha224sum, sha256sum, sha384sum, sha512sum [1]
* dirname
* basename
* mkfifo
* mknod
* chmod

The following additional coreutils are implemented and tested, but are not provided in GNU coreutils:
* hashfile: A generic driver for the md5sum, sha1sum, etc.
* which: Finds executable programs in PATH. 

The following library is provided:
* chmod-parse: Parses a mode in a form acceptable to the chmod command,
 except that `--reference` modes are not handled. 

Additionally, all coreutils install with appropriate man pages,
 if the help2man program is available in the host, and they are not disabled.

[1]: All of these programs are built as aliases of `hashfile`. 


## Building with cmake

You can build lc-coreutils with cmake. For most installations, 
 the default configuration is sufficient, simply enter a different directory from the source and run cmake:
* `cmake -DCMAKE_BUILD_TYPE=Release <path-to-source-dir>`.

If you want debugging symbols, you can omit the `CMAKE_BUILD_TYPE`:
* `cmake <path-to-source-dir>`

By default lc-coreutils installs to appropriate subdirectories of `CMAKE_INSTALL_PREFIX`,
 which defaults to `/usr/local`. If you wish to install to a different directory, 
 you can specify the value of `CMAKE_INSTALL_PREFIX`:
* `cmake -DCMAKE_INSTALL_PREFIX=/path/to/prefix <path-to-source-dir>`.

Additionally, the programs use cmake's GNUInstallDirs.
 You can install the main programs in a path relative to `CMAKE_INSTALL_PREFIX`, 
 and sysadmin programs to a custom location by additionally specifying `CMAKE_INSTALL_SBINDIR`:
* `cmake -DCMAKE_INSTALL_SBINDIR=/path/to/sbin <path-to-source-dir>`

Similarily, you can keep the default location for sysadmin programs, and change the install path for the main programs,
 by specifying `CMAKE_INSTALL_BINDIR`. You can also specify both together. 
 If both are relative to the same directory, it may be easier to specify `CMAKE_INSTALL_PREFIX`
* `cmake -DCMAKE_INSTALL_BINDIR=/path/to/bin <path-to-source-dir>`
* `cmake -DCMAKE_INSTALL_BINDIR=/path/to/bin -DCMAKE_INSTALL_SBINDIR=/other/path/to/sbin <path-to-source-dir>`
 

Building with cmake inline with the source directory (IE. `cmake .`)
 is not supported, however, you can create a build directory under the source directory (usually `build` or `cmake-build`).

There are no further limitations on how you can build using cmake. 

Presently native windows (including mingw) is neither supported nor tested. 
 Many of the programs use posix-specific functions, which are likely unavailable in windows. 
Additionally, building on cygwin is not supported. Numerous test failures occur on cygwin w/o explanation. 

If you only want to build specific coreutils,
 you can specify them in `LCNIX_ENABLE_COREUTILS`.
See the list of implemented coreutils above 

* note that specifying `hashfile` is necessary and sufficient to build any of the subprograms
 of hashfile. 
 Specifying any of those in `LCNIX_ENABLE_COREUTILS` will cause an error. 
 Instead specify them in `LCNIX_COREUTILS_HASHSUM_ALIASES` instead. 

lc-coreutils is lcnix bootstrap aware. 
A cmake superproject may set the `LCNIX_BOOTSTRAP_LIBC` and `LCNIX_BOOTSTRAP_CXXSTDLIB`
 to the names of STATIC library targets in the same project. 
 This will cause lc-coreutils to build against that libc (using `-static -nostdlib`)
  (and that c++ stdlib).
 The behaviour is undefined if either variable is set to the name of a SHARED library, 
 or to a string that is not the name of a target. 


## Running tests

lc-coreutils comes with its own test-suite using ctest. 
After building with cmake, you can run ctest in the build directory.

All tests should pass with the following *known* issues:
* The link test suite, as well as the ln tests which mention `hard` links (ie. `ln-hard-target`)
  will likely fail on filesystems which do not support hard links (such as FAT32). These tests will also likely fail if the source and build directories are on different file systems. 
* All tests (except in chmod-parse) which test for mode (ie. that have '-mode' in the name),
  and all chmod tests, will likely not work on filesystems that do not support unix style permissions (including FAT32 and NTFS). 
* The mkfifo, mknod, and nohup test suites may fail on filesystems that do not support named pipe files. (nohup uses a named pipe as a interprocess synchronization primitive). 

Beyond the known failures, 
 any test suite failure is a bug and should be reported to the lc-coreutils issue tracker,
 <https://github.com/LightningCreations/lc-coreutils/issues>. 

Please indicate the which test(s) failed, and any additional information
 (for example, if they reported a SEGMENTATION FAULT or BAD COMMAND),
 It is recommend to tag the issue with the appropriate coreutil (the first part of the test name,
  or `chmod-parse` if the test name starts with `chmod-parse`).
 Also include information about your system, IE. which linux distro and version.
 
 
The tests are run by CI, so failures should be rare, 
 but it is still recommended that you run the test suite
 (especially if succesfully building on an unsupported or untested platform).


## Hacking/Modifying lc-coreutils

If you want to implement a missing feature, add a missing coreutil, 
 or fix a bug, you can. 

In all cases, you are encouraged to add test cases for anything you implement. 

Before reporting a test suite failure in a modified branch,
 ensure that it is reproducible on a clean (unmodified) clone of lc-coreutils. 

## Copyright

Copyright (C) 2020  Lightning Creations

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>
