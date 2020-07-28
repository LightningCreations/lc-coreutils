//
// Created by chorm on 2020-07-22.
//

#include "chmod-parse.h"
#include <error.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

mode_t parse_mode(const char* i_md,mode_t mode,_Bool dir,mode_t umask){
    char* md = strdup(i_md);
    if(*md=='+'&&(*(md+1)>='0'&&*(md+1)<'8'))
        mode |= strtol(md+1,NULL,8);
    else if(*md=='-'&&(*(md+1)>='0'&&*(md+1)<'8'))
        mode &= ~strtol(md+1,NULL,8);
    else if(*md=='='&&(*(md+1)>='0'&&*(md+1)<'8'))
        mode = strtol(md+1,NULL,8);
    else if((*md>='0'&&*md<'8'))
        mode = strtol(md,NULL,8) | (dir?mode&06000:0);
    else
    {
        char *opt = strtok(md, ",");
        while(opt) {
            if (strlen(opt) < 2)
                error(1, 0, "Invalid mode selector %s", i_md);
            mode_t mask = 0;
            mode_t b_val = 0;
            if (*opt && (*opt == '-' || *opt == '+' || *opt == '-'))
                mask = 07777 & ~umask;
            while (*opt != '-' && *opt != '+' && *opt != '-')
                switch (*opt++) {
                    case 'u':
                        mask |= 04700;
                        break;
                    case 'g':
                        mask |= 02070;
                        break;
                    case 'o':
                        mask |= 01007;
                        break;
                    case 'a':
                        mask |= 07777;
                        break;
                    default:
                        error(1, 0, "Invalid mode selector %s", i_md);
                }
            do {
                char sw = *opt++;
                if (*opt == 'u') {
                    mode_t v = (mode & 0700) >> 6;
                    b_val = (v<<6) | (v<<3) | v;
                }else if (*opt == 'g') {
                    mode_t v = (mode & 070) >> 3;
                    b_val = (v<<6) | (v<<3) | v;
                }else if (*opt == 'o') {
                    mode_t v = (mode & 07);
                    b_val = (v<<6) | (v<<3) | v;
                }else
                    while (1) {
                        if (*opt == 's')
                            b_val |= 06000;
                        else if (*opt == 'r')
                            b_val |= 0444;
                        else if (*opt == 'w')
                            b_val |= 0222;
                        else if (*opt == 'x')
                            b_val |= 0111;
                        else if (*opt == 't')
                            b_val |= 01000;
                        else if (*opt == 'X')
                            b_val |= (dir || mode & 0111) ? 0111 : 0;
                        else if(!*opt || *opt == '+'|| *opt == '-' || *opt == '=') {
                            break;
                        }else if(*opt)
                            error(1, 0, "Invalid mode selector %s", i_md);
                        opt++;
                    }
                b_val &= mask;
                // Remove the bits for now, if its +, union them, it its =, discard, if its -, set difference
                switch (sw) {
                    case '+':
                        mode |= b_val;
                        break;
                    case '-':
                        mode &= ~b_val;
                        break;
                    case '=':
                        mode = (mode&(~mask)) | b_val | (dir ? mode & 06000 : 0);
                        break;
                    default:
                        error(1, 0, "Invalid mode selector");
                }
            }while(*opt);
            opt = strtok(NULL, ",");
        }
    }
    return mode;
}
