#include "error.h"

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

__attribute__((__format__(printf,3,4))) void error(int exitc,int errn,const char* fmt,...) {
    va_list ap;
    va_start(ap,fmt);
    vfprintf(stderr,fmt,ap);
    va_end(ap);
    if(errn)
        fprintf(stderr,": %s",strerror(errn));
    fprintf(stderr,"\n");
    if(exitc)
        exit(exitc);
}
