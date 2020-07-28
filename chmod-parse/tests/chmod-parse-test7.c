//
// Created by chorm on 2020-07-27.
//
#include <sys/types.h>
#include <chmod-parse.h>

int main(void){
    if(parse_mode("-755",0777,0,022)!=022)
        return 1;
}
