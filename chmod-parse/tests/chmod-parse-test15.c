//
// Created by chorm on 2020-07-27.
//
#include <sys/types.h>
#include <chmod-parse.h>

int main(void){
    if(parse_mode("g=u",0700,0,022)!=0770)
        return 1;
}
