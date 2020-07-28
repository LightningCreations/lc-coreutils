//
// Created by chorm on 2020-07-11.
//

#include <version.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <error.h>
#include <stdlib.h>

#include <chmod-parse.h>

int main(int argc,char** argv){
    _Bool mkparents = 0;
    _Bool verbose = 0;
    _Bool done_opts = 0;
    mode_t mode = 0777;
    char* prg_name = argv[0];
    static const char* HELP =
            "Usage: %s [OPTIONS...] [DIRECTORY..]\n"
            "Creates each of the provided directories\n"
            "\t--version: Prints version information and exits\n"
            "\t--help: Prints this message and exits\n"
            "\t-m,--mode=<mode>: Sets the base to create the directory with, instead of 777&(~umask)\n"
            "\t-p,--parents: Creates all parents of each directory and ignores existing directories\n"
            "\t-v,--verbose: Prints a message for each directory created\n"
    ;
    (void)argc;
    argv++;
    for(;*argv;argv++){
        char* arg = *argv;
        if(done_opts||*arg!='-'){
            done_opts = 1;
            if(!mkparents){
                if(mkdir(arg,mode)<0){
                    error(1,errno,"Could not create directory %s",arg);
                    abort();
                    // No CLion this is unreachable
                }
                if(verbose)
                    printf("Created directory: %s\n",arg);
            }else{
                char* arg_copy = calloc(strlen(arg)+1,1);
                char* c = strtok(arg,"/");
                int dir_fd;
                if(strcmp(c,"")==0) {
                    dir_fd = open("/", O_RDONLY|O_DIRECTORY);
                }else
                    dir_fd = AT_FDCWD;
                if(dir_fd==-1)
                    error(1,errno,"Could not stat search base");
                do{
                    strcat(arg_copy,c);
                    strcat(arg_copy,"/");
                    if(strcmp(c,"")==0)
                        continue;
                    int tmp = openat(dir_fd,c,O_RDONLY|O_DIRECTORY);
                    if(tmp<0) {
                        if(mkdirat(dir_fd,c,mode)<0&&errno!=EEXIST)
                            error(1,errno,"Failed to create directory: %s",arg_copy);
                        if((tmp = openat(dir_fd,c,O_RDONLY|O_DIRECTORY))<0)
                            error(1,errno,"Failed to open created directory: %s",arg_copy);
                        if(verbose)
                            printf("Created directory: %s\n",arg_copy);
                    }
                    close(dir_fd);
                    dir_fd = tmp;
                }while((c = strtok(NULL,"/")));
                free(arg_copy);
            }
        }else{
            arg++;
            if(*arg=='-'){
                arg++;
                if(strcmp(arg,"version")==0) {
                    printf(VERSION, "mkdir");
                    return 0;
                }else if(strcmp(arg,"parents")==0)
                    mkparents = 1;
                else if(strcmp(arg,"verbose")==0)
                    verbose = 1;
                else if(strcmp(arg,"help")==0){
                    printf(HELP,prg_name);
                    return 0;
                }else if(strncmp(arg,"mode",4)==0){
                    arg+=4;
                    if(*arg!='='){
                        printf(HELP,prg_name);
                        return 1;
                    }
                    mode_t um = umask(0);
                    mode &= ~um;
                    arg++;
                    mode = parse_mode(arg,mode,1,um);
                }else if(!*arg)
                    done_opts = 1; // Allow `--` to signify the end of the options
                else{
                    printf(HELP,prg_name);
                    return 1;
                }
            }else while(*arg){
                if(*arg=='p')
                    mkparents = 1;
                else if(*arg=='v')
                    verbose = 1;
                else if(*arg=='m'){
                    arg++;
                    mode_t um = umask(0);
                    mode &= ~um;
                    if(*arg)
                        mode = parse_mode(arg,mode,1,um);
                    else if(*argv++){
                        mode = parse_mode(*argv,mode,1,um);
                    }else{
                        printf(HELP,prg_name);
                        return 1;
                    }
                    break;
                }else{
                    printf(HELP,prg_name);
                    return 1;
                }
                arg++;
            }
        }
    }
}