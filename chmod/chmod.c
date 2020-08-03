//
// Created by chorm on 2020-07-17.
//

#define _DEFAULT_SOURCE
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
#include <stdlib.h>

enum DiagnosticMode{
    Silent=-1,
    Normal=0,
    Changes=1,
    Verbose=2
};

void update_recursive_reference(int fd,mode_t m,const char* name_buf,mode_t um,enum DiagnosticMode diag){
    struct stat st;
    fstat(fd,&st);
    if(fchmod(fd,m)<0){
        if(diag<Normal)
            exit(1);
        else
            error(1,errno,"Could not update mode of %s to %04o",name_buf,m);
    }else if(diag>=Changes){
        if(m!=st.st_mode)
            printf("Updated mode of %s to %04o",name_buf,m);
        else if(diag>Changes)
            printf("Retained mode of %s as %04o",name_buf,m);
    }
    if(S_ISDIR(st.st_mode)) {
        DIR *dir = fdopendir(fd);
        struct dirent* ent;
        while((ent = readdir(dir))){
            if(ent->d_type==DT_LNK)
                continue;
            else if(ent->d_type==DT_UNKNOWN){
                fstatat(fd,ent->d_name,&st,AT_SYMLINK_NOFOLLOW);
                if(S_ISLNK(st.st_mode))
                    continue;
            }
            if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
                continue;
            char *n_buf = malloc(strlen(name_buf) + 1 + strlen(ent->d_name));
            strcpy(n_buf, name_buf);
            strcat(n_buf,"/");
            strcat(n_buf,ent->d_name);
            int f = openat(fd,ent->d_name,O_RDONLY);
            update_recursive_reference(f,m,n_buf,um,diag);
            free(n_buf);
        }
    }
}

void update_recursive(int fd,const char* md,const char* name_buf,mode_t um,enum DiagnosticMode diag){
    struct stat st;
    if(fstat(fd,&st))
        error(1,errno,"Cannot stat %s",name_buf);
    mode_t m = parse_mode(md,st.st_mode&07777,S_ISDIR(st.st_mode),um);
    if(m<0)
        error(1,errno,"Invalid mode specified %s",md);

    if(fchmod(fd,m)<0){
        if(diag<Normal)
            exit(1);
        else
            error(1,errno,"Could not update mode of %s to %04o",name_buf,m);
    }else if(diag>=Changes){
        if(m!=st.st_mode)
            printf("Updated mode of %s to %04o",name_buf,m);
        else if(diag>Changes)
            printf("Retained mode of %s as %04o",name_buf,m);
    }
    if(S_ISDIR(st.st_mode)) {
        DIR *dir = fdopendir(fd);
        struct dirent* ent;
        while((ent = readdir(dir))){
            if(ent->d_type==DT_LNK)
                continue;
            else if(ent->d_type==DT_UNKNOWN){
                fstatat(fd,ent->d_name,&st,AT_SYMLINK_NOFOLLOW);
                if(S_ISLNK(st.st_mode))
                    continue;
            }
            if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
                continue;
            char *n_buf = malloc(strlen(name_buf) + 1 + strlen(ent->d_name));
            strcpy(n_buf, name_buf);
            strcat(n_buf,"/");
            strcat(n_buf,ent->d_name);
            int f = openat(fd,ent->d_name,O_RDONLY);
            update_recursive(f,md,n_buf,um,diag);
            free(n_buf);
        }
    }
}

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
        "Options:\n"
        "\t-c, --changes: Report on changed modes and errors\n"
        "\t-v, --verbose: Report on all actions, even when chmod doesn't change permissions\n"
        "\t-q, --quiet, --silent: Silence all messages, even errors.\n"
        "\t-R, --recursive: Operates recursively on children of directories\n"
        "\t--preserve-root: Fail to operate recursively on / \n"
        "\t--no-preserve-root: Don't treat / differently from any other directory (default)\n"
        "\t--reference=FILE: Uses the file permissions on FILE, rather than a textual or octal mode\n"
        "\t--help: Prints this message and exits\n"
        "\t--version: Prints version information and exits\n";

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
            }else if(strcmp(arg,"version")==0){
                printf(VERSION,"chmod");
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
    _Bool reference_mode = 0;
    struct stat st;
    if(strncmp(md_mopt,"--reference=",12)==0){
        const char* f = md_mopt+12;
        if(stat(f,&st)<0) {
            if (diag_mode < Normal)
                exit(1);
            else
                error(1, errno, "Cannot stat reference file %s", f);
        }
        reference_mode = 1;
        md = st.st_mode&07777;
    }
    mode_t um = umask(0); // Syscalls won't need it passed this point, just set it to 0.
    for(;*argv;argv++){
        int fd = open(*argv,O_RDONLY);
        if(fd<0) {
            if (diag_mode < Normal)
                exit(1);
            else
                error(1, errno, "Cannot stat file %s", *argv);
        }
        if(!recurse) {
            if(fstat(fd,&st)<0) {
                if (diag_mode < Normal)
                    exit(1);
                else
                    error(1, errno, "Cannot stat file %s", *argv);
            }
            _Bool dir = S_ISDIR(st.st_mode);
            if (!reference_mode)
                md = parse_mode(md_mopt, st.st_mode & 07777, dir, um);
            if(md<0)
                error(1,errno,"Invalid mode specified %s",md_mopt);
            if (fchmod(fd, md) < 0) {
                if (diag_mode < Normal)
                    exit(1);
                else
                    error(1, errno, "Could not update mode on file %s to %04o", *argv,md);
            }
            if (md != (st.st_mode & 07777) && diag_mode >= Changes)
                printf("Updated mode of %s to %04lo\n", *argv, (unsigned long) md);
            else if (diag_mode == Verbose)
                printf("Retained mode of %s as %04lo\n", *argv, (unsigned long) md);
        }else{
            if(reference_mode)
                update_recursive_reference(fd,md,*argv,um,diag_mode);
            else
                update_recursive(fd,md_mopt,*argv,um,diag_mode);
        }
    }
}


