#ifndef LCCOREUTILS_ERROR_H_2020_10_29_20_36_40  
#define LCCOREUTILS_ERROR_H_2020_10_29_20_36_40

#include <errno.h>

///
/// Implementation of the GNU Error function.
/// Prints an error message designated by fmt, and strerror(errn) if it is nonzero.
/// Afterwards, exits with exitc if it is nonzero
__attribute__((__format__(printf,3,4))) void error(int exitc,int errn,const char* fmt,...);

#endif