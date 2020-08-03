//
// Created by chorm on 2020-07-17.
//

#include <string.h>
#include <stdio.h>
#include <libgen.h>

#include <version.h>

int main(int argc,char** argv){
    const char* prg_name = *argv++;
    static const char* HELP =
            "Usage: %s [OPTION] NAMES...\n"
            "Prints each of NAMES... with the last non-slash component, and trailing slashes removed.\n\n"
            "Options:\n"
            "\t-z, --zero: Prints a NUL byte between the output NAMES..., rather than a newline\n"
            "\t--version: Prints version information and exits\n"
            "\t--help: Prints this message and exits\n";
    char sep = '\n';
    if(!*argv) {
        printf(HELP, prg_name);
        return 1;
    }else if(**argv=='-'){
        if(strcmp(*argv,"--version")==0){
            printf(VERSION,"dirname");
            return 0;
        }else if(strcmp(*argv,"--version")==0){
            printf(HELP,prg_name);
            return 0;
        }else if(strcmp(*argv,"--zero")==0||strcmp(*argv,"-z")==0)
            sep = '\0';
        argv++;
        if(!*argv) {
            printf(HELP, prg_name);
            return 1;
        }
    }
    for(;*argv;argv++)
        printf("%s%c",dirname(*argv),sep);
}