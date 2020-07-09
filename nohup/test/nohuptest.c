//
// Created by chorm on 2020-07-09.
//

#define _GNU_SOURCE

#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>

#include <pthread.h>

void discard(int _signal){
    (void)_signal;
}

void* send_signals_to_pid(void* v){
    pid_t p = (pid_t)v;
    kill(p,SIGHUP);
    kill(p,SIGUSR1);
    return NULL;
}

int main(int argc,char** argv){
    char* nohup_exec = argv[1];
    char* nohuptest0_exec = argv[2];
    pid_t pid;
    int sig;
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set,SIGUSR2);
    signal(SIGUSR2,SIG_BLOCK);
    if(!(pid=fork())){
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);
        // The child process doesn't need stdin/stdout/stderr. Close them so nohup doesn't have to redirect them
        execl(nohup_exec,nohuptest0_exec,NULL);
        return 1;
    }else{
        int status;
        signal(SIGUSR2,discard);
        pause();
        pthread_t thread;
        pthread_create(&thread,NULL,send_signals_to_pid,(void*)pid);
        if(waitpid(pid,&status,0))
            return status;
        else
            return 0;
    }
}
