#define _GNU_SOURCE

#include <version.h>
#include <stdio.h>
#include <error.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int main(int argc,char** argv){
    if(argc<2)
        error(1,0,"Usage: %s [OPTIONS]... DIRECTORY..",argv[0]);
    else{
        const char* prg_name = *argv++;
        _Bool nofail_nonempty =0;
        _Bool verbose = 0;
        _Bool parents = 0;
        _Bool opts_done = 0;
        for(;*argv;argv++){
            char* opt = *argv;
            if(opts_done||opt[0]!='-'){
                opts_done = 1;
                if(rmdir(opt)==0){
                    if(verbose)
                        fprintf(stderr,"Removed File %s",opt);
                    if(parents){
                        char* sh;
                        while((sh=memrchr(opt,'/',strlen(opt)))&&sh!=opt){
                            *sh = 0;
                            if(rmdir(opt)<0){
                                if(!((errno==EEXIST||errno==ENOTEMPTY)&&nofail_nonempty))
                                    error(1,errno,"Failed to remove directory %s",opt);
                                break;
                            }else{
                                if(verbose)
                                    fprintf(stderr,"Removed File %s",opt);
                            }
                        }
                    }
                }else if(!((errno==EEXIST||errno==ENOTEMPTY)&&nofail_nonempty))
                    error(1,errno,"Failed to remove directory %s",opt);
            }else if(opt[1]!='-'){
                opt++;
                for(;*opt;opt++)
                    if(*opt=='p')
                        parents = 1;
                    else if(*opt=='v')
                        parents = 2;
                    else
                        error(1,0,"Unknown Option -%c",*opt);
            }else if(strcmp(opt,"--version")==0){
                printf(VERSION,"rmdir");
                return 0;
            }else if(strcmp(opt,"--help")==0){
                const char HELP[] = "Usage: %s [OPTIONS]... DIRECTORY...\n"
                "Removes all of the specified directories, if they are empty\n"
                "Options:\n"
                "\t--ignore-fail-on-non-empty: Silently ignore non-empty directories, instead of erroring\n"
                "\t-p, --parents: Remove all parent components as well. For example, if DIRECTORY is foo/bar/baz, also removes foo/bar and foo\n"
                "\t-v, --verbose: Prints a diagnostic message for each removed directory\n"
                "\t--help: Prints this message, and exits\n"
                "\t--version: Prints version information and exits\n";

                printf(HELP,prg_name);
                return 0;
            }else if(strcmp(opt,"--ignore-fail-on-non-empty")==0)
                nofail_nonempty = 1;
            else if(strcmp(opt,"--parents")==0)
                parents = 1;
            else if(strcmp(opt,"--verbose")==0)
                verbose = 1;
            else
                error(1,0,"Unrecognized option %s",opt);
        }
    }
}