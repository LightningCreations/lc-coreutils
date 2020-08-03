//
// Created by chorm on 2020-07-28.
//
#define _DEFAULT_SOURCE
#include <version.h>
#include <chmod-parse.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <error.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysmacros.h>
#include <errno.h>

int main(int argc,char** argv){
    const char* HELP =
            "Usage: %s [OPTIONS]... NAME TYPE [MAJOR MINOR]\n"
            "Creates a special file with a given type\n\n"
            "Options:\n"
            "\t-m,--mode=MODE: Sets the mode to MODE, rather than =rw\n"
            "\t--version: Prints version information and exits\n"
            "\t--help: Prints this message and exits\n"
            "\n"
            "TYPE must be one of p (fifo/named pipe), b (buffered device), c or u (both unbuffered devices)\n"
            "Note that on most operating systems, an unprivileged user will only be able to use this command to create named pipes\n"
            "When any of b, c, or u is specified as the TYPE, both MAJOR and MINOR must be specified. Otherwise, they must be omitted\n";
    const char* prg_name = *argv++;
    mode_t mode = 0666;
    dev_t dev = 0;
    for(;*argv&&**argv=='-';argv++){
        char* arg = (*argv)+1;
        if(*arg=='m'){
            if(*++arg);
            else if(!argv[1])
                error(1,0,HELP,prg_name);
            else
                arg = argv[1];
            mode_t um = umask(0);
            mode = parse_mode(arg,0,0,um);
            if(mode<0)
                error(1,errno,"Invalid mode specified %s",arg);
        }else if(*arg=='-'){
            arg++;
            if(strcmp(arg,"version")==0){
                printf(VERSION,"mknod");
                return 0;
            }else if(strcmp(arg,"help")==0){
                printf(HELP,prg_name);
                return 0;
            }else if(strncmp(arg,"mode=",5)==0){
                if(!arg[5])
                    error(1,0,HELP,prg_name);
                mode_t um = umask(0);
                mode = parse_mode(arg+5,0,0,um);
                if(mode<0)
                    error(1,errno,"Invalid mode specified %s",arg+5);
            } else
                break;
        } else
            break;
    }
    if(!*argv)
        error(1,0,HELP,prg_name);
    const char* name = *argv++;
    if(!*argv)
        error(1,0,HELP,prg_name);
    const char* type = *argv++;
    _Bool is_dev = 0;
    switch(*type){
        case 'p':
            mode |= S_IFIFO;
        break;
        case 'b':
            mode |= S_IFBLK;
            is_dev = 1;
        break;
        case 'c':
        case 'u':
            mode |= S_IFCHR;
            is_dev = 1;
        break;
        default:
            error(1,0,"Invald device type: %s",type);
    }

    if(is_dev){
        if(!argv[0]||!argv[1])
            error(1,0,HELP,prg_name);
        dev = makedev(strtoul(argv[0],NULL,0),strtoul(argv[1],NULL,0));
    }
    if(mknod(name,mode,dev)<0)
        error(1,errno,"Could not create special file %s",name);
}
