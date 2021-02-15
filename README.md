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
* arch
* unlink
* rmdir
* link

The following additional coreutils are implemented and tested, but are not provided in GNU coreutils:
* hashfile: A generic driver for the md5sum, sha1sum, etc.
* which: Finds executable programs in PATH. 

The following library is provided:
* chmod-parse: Parses a mode in a form acceptable to the chmod command,
 except that `--reference` modes are not handled. 

Additionally, all coreutils install with appropriate man pages,
 if the help2man program is available in the host, and they are not disabled.

[1]: All of these programs are built as aliases of `hashfile`. In the future, a configuration option would be provided to provide renameable versions. As a note, these programs require a C++ library to be available at boot.


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


## Running tests

lc-coreutils comes with its own test-suite using ctest. 
After building with cmake, you can run ctest in the build directory.

All tests should pass with the following *known* issues:
* The link test suite, as well as the ln tests which mention `hard` links (ie. `ln-hard-target`)
  will likely fail on filesystems which do not support hard links (such as FAT32). These tests will also likely fail if the source and build directories are on different file systems. 
* All tests (except in chmod-parse) which test for mode (ie. that have '-mode' in the name),
  and all chmod tests, will likely not work on filesystems that do not support unix style permissions (including FAT32 and NTFS). 
* The mkfifo, mknod, and nohup test suites may fail on filesystems that do not support named pipe files. (nohup uses a named pipe as a interprocess synchronization primitive). 

(Note: mknod does not test block or character device files, due to the nature of them, and the dependence on a privileged process)

Beyond the known failures, 
 any test suite failure (except on an unsupported system) is a bug and should be reported to the lc-coreutils issue tracker,
 <https://github.com/LightningCreations/lc-coreutils/issues>. 

Please indicate the which test(s) failed, and any additional information
 (for example, if they reported a SEGMENTATION FAULT or BAD COMMAND),
 It is recommend to tag the issue with the appropriate coreutil (the first part of the test name,
  or `chmod-parse` if the test name starts with `chmod-parse`).
 Also include information about your system, IE. which linux distro and version.
 
 
The tests are run by CI, so failures should be rare, but it is still recommended that you run the test suite
 (especially if succesfully building on an unsupported or untested platform).


If you have valgrind installed, you can set the cmake variable `LCNIX_COREUTILS_VALGRIND_TESTS` (with `-DLCNIX_COREUTILS_VALGRIND_TESTS=ON` when configuring) to run valgrind tests on some coreutils. 
Valgrind tests are generally not necessary to run, as they are run in CI, and are unlikely to change between environments, and they can take considerably longer than the regular tests (particularily on `Debug` builds), and do not necessarily test the correctness of the implementation, but are focused on testing if there are memory issues (such as memory leaks, buffer overflows, etc.). Note that valgrind tests have limited coverage compared to the normal tests (presently only `chmod-parse`, `true`, `false`, and `hashfile` are covered by valgrind tests). 

### Running tests with sanitizers

You can build and run lc-coreutils, as well as all tests, with any sanitizer supported by your host C and C++ compiler, by providing it in the cmake variable `LCNIX_ENABLE_SANITIZER`. 

All sanitizers are supported, and the utilities should pass all test cases when built with sanitizers. 

When reporting a Test Suite failure caused by a sanitizer, indicate which sanitizer is enabled and which compiler.

CI builds and test with the `undefined`, `address`, and `memory` sanitizers. 

## Hacking/Modifying lc-coreutils

If you want to implement a missing feature, add a missing coreutil, 
 or fix a bug, you can. 

In all cases, you are encouraged to add test cases for anything you implement. 

Before reporting a test suite failure in a modified branch,
 ensure that it is reproducible on a clean (unmodified) clone of lc-coreutils.

If the test suite failure is caused by a test added by you, which tests an existing behaviour of lc-coreutils,
 instead ensure the following: 
* The test is either of behaviour mandated by POSIX or the Linux Standards Base, or is a well-defined feature of
 GNU Coreutils, or otherwise provided by lc-coreutils (with ascending order of priority), or tests for memory errors (such as valgrind tests)
* The failure is caused by an existing part of the lc-coreutils, which is unmodified from the upstream repository
 (this can be observed, if modified, by copying the current git branch, then checking out the file from the upstream HEAD)
* An issue filed links to the code used to test the behaviour. 
* The failure is not specific to an environment that may not support the documented behaviour (for example, hard links on a FAT32 filesystem)
* If a failure is fixed by a modification made by you, you are encouraged to file a pull request with the test and the modification together. You should still file a separate issue with the test, 

Test Suite Requirements:
* Each test in a test suite in the coreutil shall depend **only** on that utility from lc-coreutils. This is to avoid test failures that are caused by a defect in a different program (as well as to allow users to choose the utilities built by this package without breaking the test suite). 
* The test suite may assume the existence, and compliance, of any tool defined by posix, including those for which a supplementary program is built by this package. In the latter case, the test suite MUST use the program provided by the host system, not the utility built by this package. 

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
