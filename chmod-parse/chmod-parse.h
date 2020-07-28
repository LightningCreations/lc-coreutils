//
// Created by chorm on 2020-07-22.
//

#ifndef LCNIX_CHMOD_PARSE_H
#define LCNIX_CHMOD_PARSE_H

#include <sys/types.h>

mode_t parse_mode(const char* md,mode_t mode,_Bool dir,mode_t umask);

#endif //LCNIX_CHMOD_PARSE_H
