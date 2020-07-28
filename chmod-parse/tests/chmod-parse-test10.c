//
// Created by chorm on 2020-07-27.
//
#include <sys/types.h>
#include <chmod-parse.h>

int main(void){
    if(parse_mode("u+rwx",0,0,022)!=0700)
        return 1;
}
