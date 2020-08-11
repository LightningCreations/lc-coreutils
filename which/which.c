//
// Created by chorm on 2020-08-11.
//

#include <error.h>
#include <version.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/limits.h>
#include <unistd.h>

int main(int argc,char** argv){
    const char* const path = getenv("PATH");
    const char* HELP = {
            "Usage: %s [OPTIONS] filename...\n"
            "Finds programs on PATH which can be executed from the shell\n\n"
            "Options:\n"
            "\t-a: Prints all matches, instead of just the first\n"
            "\t--help: Prints this message, and exits\n"
            "\t--version: Prints version information and exits\n"
    };
    _Bool stop = 1;
    if(!argv[1])
        error(1,0,HELP,argv[0]);
    if(*argv[1]=='-'){
        const char* arg = argv[1];
        if(arg[1]=='a')
            stop = 0;
        else if(strcmp(arg,"--help")==0){
            printf(HELP,argv[0]);
            return 0;
        }else if(strcmp(arg,"--version")==0){
            printf(VERSION,"which");
            return 0;
        } else
            error(1,0,HELP,argv[0]);
        argv++;
        if(!argv[1])
            error(1,0,HELP,argv[0]);
    }
    for(argv++;*argv;argv++){
        if(strstr(*argv,"/")) {
            if(access(*argv,X_OK)==0)
                printf("%s\n", *argv);
        }else{
            char buf[PATH_MAX];
            char* path_d = strdup(path);
            for(char* c = strtok(path_d,":");c;c=strtok(NULL,":")){
                size_t len = strlen(c);
                if(len==0)
                    continue;
                strcpy(buf,c);
                if(c[len-1]!='/')
                    strcat(buf,"/");
                strncat(buf,*argv,PATH_MAX-len);
                if(access(buf,X_OK)==0){
                    printf("%s\n",buf);
                    if(stop)
                        break;
                }
            }
        }
    }

}
