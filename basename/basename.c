//
// Created by chorm on 2020-07-17.
//

#include <string.h>
#include <stdio.h>
#include <libgen.h>
#include <error.h>

#include <version.h>

int main(int argc,char** argv){
    const char* prg_name = *argv++;
    static const char* HELP =
            "Usage: %s NAME [SUFFIX]\n"
            "\tor: %s [OPTION]... NAME...\n"
            "Prints the last non-slash component of each of NAMES... ignoring trailing slashes.\n\n"
            "Options:\n"
            "\t-z, --zero: Prints a NUL byte between the output NAMES..., rather than a newline\n"
            "\t--version: Prints version information and exits\n"
            "\t--help: Prints this message and exits\n";
    char sep = '\n';
    const char* suffix = "";
    _Bool all = 0;
    _Bool accept_suffix = 1;
    if(!*argv) {
        printf(HELP, prg_name);
        return 1;
    }else while(**argv=='-'){
        accept_suffix = 0;
        if((*argv)[1]!='-'){
            accept_suffix = 0;
            char* opt = (*argv)+1;
            for(;*opt;opt++)
                if(*opt=='s'){
                    if(*++opt)
                        suffix = opt;
                    else
                        suffix = *++argv;
                    break;
                }else if(*opt=='z')
                    sep = '\0';
                else if(*opt=='a')
                    all = 1;

        }else if(strcmp(*argv,"--version")==0){
            printf(VERSION,"basename");
            return 0;
        }else if(strcmp(*argv,"--version")==0){
            printf(HELP,prg_name);
            return 0;
        }else if(strcmp(*argv,"--zero")==0){
            sep = '\0';
        }else if(strncmp(*argv,"--suffix=",9)==0){
            suffix = (*argv)+9;
            all = 1;
        }else if(strcmp(*argv,"--multiple")==0)
            all = 1;
        argv++;
        if(!*argv) {
            printf(HELP, prg_name,prg_name);
            return 1;
        }
    }

    if(accept_suffix&&argv[1]){
        suffix = argv[1];
    }
    
    int suffix_len = strlen(suffix);

    if(all) for(;*argv;argv++){
        char* n = basename(*argv);
        int i = strlen(n);
        if(i>=suffix_len){
            if(strcmp(n+(i-suffix_len),suffix)==0)
                n[i-suffix_len] = '\0';
        }
        printf("%s%c",n,sep);
    }else{
        char* n = basename(*argv);
        int i = strlen(n);
        if(i>=suffix_len){
            if(strcmp(n+(i-suffix_len),suffix)==0)
                n[i-suffix_len] = '\0';
        }
        printf("%s%c",n,sep);
    }
}