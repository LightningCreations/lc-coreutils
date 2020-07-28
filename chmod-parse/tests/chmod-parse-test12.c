//
// Created by chorm on 2020-07-27.
//
#include <sys/types.h>
#include <chmod-parse.h>

int main(void){
    if(parse_mode("g+srwx",0,0,022)!=02070)
        return 1;
}
