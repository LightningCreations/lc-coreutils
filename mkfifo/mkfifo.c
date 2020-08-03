//
// Created by chorm on 2020-07-27.
//

#include <version.h>
#include <chmod-parse.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <error.h>
#include <errno.h>

int main(int argc,char** argv){
    const char* HELP =
            "Usage: %s [OPTIONS]... NAME...\n"
            "Creates a fifo (named pipe) file with a given name.\n\n"
            "Options:\n"
            "\t-m, --mode=<MODE>: Uses MODE instead of =rw\n"
            "\t--help: Displays this message and exits\n"
            "\t--version: Displays version information and exits\n"
            ;
    char* prg_name = *argv++;
    mode_t mode = 0666;
    _Bool done_opts = 0;
    for(;*argv;argv++){
        const char* arg = *argv;
        if(!done_opts&&*arg=='-'){
            arg++;
            if(*arg=='-'){
                arg++;
                if(strcmp("help",arg)==0) {
                    printf(HELP, prg_name);
                    return 0;
                }else if(strcmp("version",arg)==0){
                    printf(VERSION,"mkfifo");
                    return 0;
                }else if(strncmp("mode=",arg,5)==0){
                    arg+=5;
                    if(!*arg)
                        error(1,0,HELP,prg_name);
                    mode_t um = umask(0);
                    mode = parse_mode(arg,0,0,um);
                    if(mode<0)
                        error(1,errno,"Invalid mode specified %s",arg);
                }
            }else if(*arg=='m'){
                if(!argv[1])
                    error(1,0,HELP,prg_name);
                mode_t um = umask(0);
                mode = parse_mode(argv[1],0,0,um);
                argv++;
            }else
                error(1,0,HELP,prg_name);
        }else{
            done_opts = 1;
            mkfifo(arg,mode);
        }
    }
}