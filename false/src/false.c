#include <stdio.h>
#include <stddef.h>
#include <version.h>
#include <string.h>

int main(int argc, char** argv) {
    if(argv[1] != NULL){
        if(strcmp(argv[1],"--version")==0)
            printf(VERSION,argv[0]);
        else if(strcmp(argv[1],"--help")==0){
            static const char* HELP =
                    "Usage: %s [--version|--help] [other ignored parameter]\n"
                    "A program that unconditionally produces an error return value\n"
                    "\t--version: Prints version information and exits\n"
                    "\t--help: Prints this message and exits\n"
            ;
            printf(HELP,argv[0]);
        }
    }
    return 1;
}
