//
// Created by chorm on 2020-07-14.
//

#include <version.h>

#include <string.h>
#include <stdio.h>

int main(int argc,char** argv){
    static const char* HELP =
            "Usage: %s [STRINGS...]\n"
            "\tor: %s OPTION\n"
            "Repeatedly outputs a line with STRINGS... or a single 'y' when omitted\n\n"
            "Options:\n"
            "\t--version: Prints version information and exits\n"
            "\t--help: Prints this message and exits\n";
    if(argv[1]&&strcmp(argv[1],"--version")==0)
        printf(VERSION,"yes");
    else if(argv[1]&&strcmp(argv[1],"--help")==0)
        printf(HELP,argv[0],argv[0]);
    else{
        for(;;)
            if(argc<2)
                puts("y");
            else {
                for (char **p = argv + 1; *p; p++)
                    printf("%s ",*p);
                puts("");
                fflush(stdout);
            }
    }
}
