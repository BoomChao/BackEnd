
/*
    杀死多个进程
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void sys_err(const char *str) 
{
    perror(str);
    exit(-1);
}


int main(int argc, char *argv[]) 
{
    pid_t pid;
    int i, n;

    if(argc < 2) {
        printf("./a.out numchild\n");
        exit(1);
    }

    n = atoi(argv[1]);
    for(i = 0; i < n; i++)
    {
        if((pid = fork()) < 0) 
            sys_err("fork");
        else if(pid == 0)
            break;
    }

    //子进程
    if(pid == 0) {
        while(1) {
            printf("I'm child pid = %d, groupid = %d\n", getpid(), getpgrp());
            sleep(1);
        }
    }

    //父进程
    if(pid > 0) {
        pid_t cpid;
        while((cpid = wait(NULL)) > 0) 
            printf("child %d is over\n", cpid);
    }


    return 0;
}

