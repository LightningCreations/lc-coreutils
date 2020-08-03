//
// Created by chorm on 2020-07-09.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

#include <version.h>

_Noreturn void print_help(int code,const char* prg_name){
    static const char HELP[] = {
            "Usage: %s COMMAND [ARGS]\n"
            "\tor: %s OPTION\n"
            "Runs the given command ignoring hangup requests\n\n"
            "Options:\n"
            "\t--help: Prints this help and exits\n"
            "\t--version: Prints version information an exits\n"
    };

    printf(HELP,prg_name,prg_name);
    exit(code);
}

int main(int argc,char** argv){
    if(argc<1)
        print_help(1,argv[0]);
    else if(*argv[1]=='-'){
        const char* opt = argv[1]+1;
        if(*opt++=='-'){
            if(strcmp(opt,"help")==0)
                print_help(0,argv[0]);
            else if(strcmp(opt,"version")==0){
                printf(VERSION,"nohup");
                return 0;
            }
        }
        print_help(1,argv[0]);
    }else{
        argv++;
        // Redirect input and outputs to files when they are otherwise attached to a terminal
        if(isatty(STDIN_FILENO)){
            puts("Ignoring input");
            int fd = open("/dev/null",O_RDONLY);
            dup2(fd,STDIN_FILENO);
            close(fd); // the handle is currently available in stdin, we don't need the original any more
        }
        if(isatty(STDOUT_FILENO)){
            puts("Redirecting stdout to nohup.out");
            int fd = open("nohup.out",O_WRONLY|O_CREAT,0666); // Set default mode for nohup.out, let umask set correct permissions
            dup2(fd,STDOUT_FILENO);
            close(fd);
        }
        if(isatty(STDERR_FILENO))
            dup2(STDOUT_FILENO,STDERR_FILENO);
        sigset_t blocked;
        sigemptyset(&blocked);
        sigaddset(&blocked,SIGHUP);
        sigprocmask(SIG_BLOCK,&blocked,NULL);
        char* prg = argv[0];
        execvp(prg,argv);
        perror("Could not execute program");
        return 1; /* If execvp returns, an error has occured, so return 1;*/ }
}