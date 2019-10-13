#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    bool printNL = 1;
    for(int i = 1; i < argc; i++) {
        if(i == 1 && strcmp(argv[i], "-n") == 0) printNL = 0;
        else {
            printf("%s", argv[i]);
            if(i < argc-1) printf(" ");
        }
    }
    if(printNL) printf("\n");
}
