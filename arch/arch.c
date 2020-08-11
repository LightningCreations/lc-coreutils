//
// Created by chorm on 2020-08-11.
//

#include <helper.h>
#include <version.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv){
    const char* HELP =
            "Usage: %s [OPTION]\n"
            "Prints the current machine architecture\n\n"
            "Options:\n"
            "\t--help: Prints this message and exits.\n"
            "\t--version: Prints version information and exits.\n";
    if(argv[1]){
        if(strcmp(argv[1],"--help")==0){
            printf(HELP,argv[0]);
            return 0;
        }else if(strcmp(argv[1],"--version")==0){
            printf(VERSION,"arch");
            return 0;
        }else{
            printf(HELP,argv[0]);
            return 1;
        }
    }

    puts(ARCH_NAME);
    return 0;
}