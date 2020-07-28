//
// Created by chorm on 2020-07-17.
//


#include <chmod-parse.h>
#include <version.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <error.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

enum DiagnosticMode{
    Silent=-1,
    Normal=0,
    Changes=1,
    Verbose=2
};


int main(int argc,char** argv){
    _Bool preserve_root = 0;
    _Bool recurse = 0;
    enum DiagnosticMode diag_mode = Normal;
    const char* md_mopt;
    char* prg_name = argv[0];

    const char* HELP =
        "Usage: %s [OPTIONS]... MODE FILES...\n"
        "\tor: %s [OPTIONS]... --reference=FILE FILES...\n"
        "Changes the permission mode on the supplied files\n\n"
        "Options:\n\n"
        "\t-c, --changes: Report on changed modes and errors\n"
        "\t-v, --verbose: Report on all actions, even when chmod doesn't change permissions\n"
        "\t-q, --quiet, --silent: Silence all messages, even errors.\n"
        "\t-R, --recursive: Operates recursively on children of directories\n"
        "\t--preserve-root: Fail to operate recursively on / \n"
        "\t--no-preserve-root: Don't treat / differently from any other directory (default)\n"
        "\t";

    argv++;
    for(;*argv;argv++){
        char* arg = *argv;
        if(*arg!='-')
            break;
        else if(strncmp(arg,"--reference",11)==0)
            break;

        arg++;
        if(*arg=='-'){
            arg++;
            if(strcmp(arg,"changes")==0)
                diag_mode = Changes;
            else if(strcmp(arg,"quite")==0||strcmp(arg,"silent")==0)
                diag_mode = Silent;
            else if(strcmp(arg,"verbose")==0)
                diag_mode = Verbose;
            else if(strcmp(arg,"recursive")==0)
                recurse =1;
            else if(strcmp(arg,"no-preserve-root")==0)
                preserve_root = 0;
            else if(strcmp(arg,"preserve-root")==0)
                preserve_root = 1;
            else if(strcmp(arg,"help")==0){
                printf(HELP,prg_name,prg_name);
                return 0;
            }
        }else if(*arg!='c'&&*arg!='f'&&*arg!='v'&&*arg!='R')
            break;
        else for(;*arg;arg++){
            if(*arg=='c')
                diag_mode = Changes;
            else if(*arg=='v')
                diag_mode = Verbose;
            else if(*arg=='f')
                diag_mode = Silent;
            else /*if(*arg=='R')*/
                recurse =1;
        }
    }
    if(!*argv){
        printf(HELP,prg_name,prg_name);
        return 1;
    }
    md_mopt = *argv++;
    if(!*argv){
        printf(HELP,prg_name,prg_name);
        return 1;
    }

    mode_t md;
    _Bool reference_mode;
    struct stat st;
    if(strncmp(md_mopt,"--reference=",12)==0){
        char* f = md_mopt+12;
        if(stat(f,&st)<0)
            error(1,errno,"Cannot stat reference file %s",f);
        reference_mode = 1;
        md = st.st_mode&07777;
    }
    mode_t um = umask(0); // Syscalls won't need it passed this point, just set it to 0.
    for(;*argv;argv++){
        int fd = open(*argv,O_RDONLY);
        if(fd<0)
            error(1,errno,"Cannot stat file %s",*argv);
        if(fstat(fd,&st)<0)
            error(1,errno,"Cannot stat file %s",*argv);
        _Bool dir = S_ISDIR(st.st_mode);
        if(!reference_mode)
            md = parse_mode(md_mopt,st.st_mode&07777,dir,um);
        if(fchmod(fd,md)<0)
            error(1,errno,"Could not update mode on file %s",*argv);
        if(md!=(st.st_mode&07777)&&diag_mode>=Changes)
            printf("Updated mode of %s to %03lo",*argv,(unsigned long)md);
        else if(diag_mode==Verbose)
            printf("Retained mode of %s as %03lo",*argv,(unsigned long)md);
    }
}


