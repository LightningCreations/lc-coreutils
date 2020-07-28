//
// Created by chorm on 2020-07-27.
//
#include <sys/types.h>
#include <chmod-parse.h>

int main(void){
    if(parse_mode("u-g",0720,0,022)!=0520)
        return 1;
}
