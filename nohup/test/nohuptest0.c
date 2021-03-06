//
// Created by chorm on 2020-07-09.
//

#define _POSIX_C_SOURCE 200809L

#include <signal.h>
#include <unistd.h>

#include <fcntl.h>


void test_usr1(int signal){
    if(signal==SIGUSR1)
        _exit(0);
    else
        _exit(1);
}

int main(void){
    int sig;
    sigset_t set;
    sigemptyset(&set);
    signal(SIGUSR1,test_usr1);
    if(openat(AT_FDCWD,"barrier",O_RDONLY)<0)
        return 1;
    pause();
    return -1; // If anything else was recieved, that isn't SIGUSR2 and doesn't quit the program, return -1
}