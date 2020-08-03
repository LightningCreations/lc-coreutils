//
// Created by chorm on 2020-07-11.
//

#include <version.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>


int main(int argc,char** argv){
    static const char* HELP =
            "USAGE: %s [OPTIONS...]\n"
            "Prints the process working directory\n\n"
            "Options:\n"
            "\t--help: Prints this message and exits\n"
            "\t--version: Prints version information and exits\n"
            "\t-L: Use the value of the PWD environment variable, even if it may contain symlinks\n"
            "\t-P: Print the absolute resolved pathname of the process working directory\n"
            "When neither -L nor -P are specified, -P is the default";
    _Bool use_env = 0;
    char* prg_name = argv[0];
    argv++;
    for(;*argv;argv++){
        char* arg = *argv;
        if(*arg!='-'){
            printf(HELP,prg_name);
            return 1;
        }else{
            arg++;
            if(*arg=='L')
                use_env = 1;
            else if(*arg=='P')
                use_env = 0;
            else if(strcmp(arg,"-version")==0){
                printf(VERSION,"pwd");
                return 0;
            }else if(strcmp(arg,"-help")==0){
                printf(HELP,prg_name);
                return 0;
            }else{
                printf(HELP,prg_name);
                return 1;
            }
        }
    }
    if(use_env)
        puts(getenv("PWD"));
    else{
        char buf[PATH_MAX];
        getcwd(buf,PATH_MAX);
        puts(buf);
    }
}