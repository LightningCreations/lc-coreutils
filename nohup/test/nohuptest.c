//
// Created by chorm on 2020-07-09.
//

#define _GNU_SOURCE

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

#include <pthread.h>

void discard(int _signal){
    (void)_signal;
}

void _at_exit(void){

}

int main(int argc,char** argv){
    char* nohup_exec = argv[1];
    char* nohuptest0_exec = argv[2];
    pid_t pid;
    mknodat(AT_FDCWD,"barrier",0666|S_IFIFO,0);
    if(!(pid=fork())){
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);
        // The child process doesn't need stdin/stdout/stderr. Close them so nohup doesn't have to redirect them
        execl(nohup_exec,nohup_exec,nohuptest0_exec,NULL);
        return 1;
    }else{
        int status;
        if(openat(AT_FDCWD,"barrier",O_WRONLY)<0)
            return 1;
        unlinkat(AT_FDCWD,"barrier",0);
        if(kill(pid,SIGHUP)<0)
            return -1;
        if(kill(pid,SIGUSR1)<0)
            return -1;
        pid_t code = waitpid(pid,&status,0);
        if(code<0)
            return -1;
        else if(code>0)
            return status;
        else
            return 0;
    }
}
