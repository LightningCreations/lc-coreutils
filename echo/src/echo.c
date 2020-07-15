// Written by Ray Redondo
// Minimal implementation of POSIX echo with GNU-style help and version.
// This file is licensed under the GNU GPL version 3 or later. For more info,
// see the COPYING file.

#include <version.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    static const char *HELP =
            "Usage: %s [OPTION] [STRING]\n" \
            "Echos the parameters to standard output\n" \
            "\t-n: Omits trailing newline" \
            "\t--version: Prints version information and exits\n" \
            "\t--help: Prints this message and exits\n";

    bool printNL = 1;
    for(int i = 1; i < argc; i++) {
        if(i == 1 && strcmp(argv[i], "-n") == 0) printNL = 0;
        else if(argc == 2 && strcmp(argv[i], "--version") == 0) {
            printf(VERSION, argv[0]);
            return 0;
        } else if(argc == 2 && strcmp(argv[i], "--help") == 0) {
            printf(HELP, argv[0]);
            return 0;
        } else {
            printf("%s", argv[i]);
            if(i < argc-1) printf(" ");
        }
    }
    if(printNL) printf("\n");
}
