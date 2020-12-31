
#include <version.h>
#include <stdio.h>
#include <error.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>


int main(int argc,char** argv){
    const char HELP[] = "Usage: %s [FILE]\n"
    "\tor: %s [OPTION]\n"
    "Removes the specified file name\n"
    "Options:\n"
    "\t--help: Prints this message and exits\n"
    "\t--version: Prints version information and exits\n";
    if(argc<2)
        error(1,0,"Usage: %s [OPTION]|[FILE]",argv[0]);
    else{
        if(strcmp(argv[1],"--help")==0){
            printf(HELP,argv[0],argv[0]);
            return 0;
        }else if(strcmp(argv[1],"--version")==0){
            printf(VERSION,"unlink");
            return 0;
        }else if(unlink(argv[1])<0){
            error(1,errno,"Failed to unlink file %s",argv[1]);
        }
    }
}
