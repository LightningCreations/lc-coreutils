//
// Created by chorm on 2020-07-13.
//

#include <version.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <error.h>
#include <errno.h>

int main(int argc,char** argv){
    static const char* HELP =
            "Usage: %s OPTION|<FILE1 FILE2>\n"
            "Creates a hard link from FILE2 to FILE1\n"
            "\t--version: Prints version information and exits\n"
            "\t--help: Prints this message and exits\n"
            ;
    if(argc==2) {
        if (strcmp(argv[1], "--version")==0) {
            printf(VERSION, argv[0]);
            return 0;
        }else if (strcmp(argv[1],"--help")==0){
            printf(HELP,argv[0]);
            return 0;
        }else{
            printf(HELP,argv[0]);
            return 1;
        }
    }else if(argc==3){
        if(link(argv[1],argv[2])<0)
            error(1,errno,"Could not create link %s to %s",argv[1],argv[2]);
        return 0;
    }else{
        printf(HELP,argv[0]);
        return 1;
    }
}