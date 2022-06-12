/*
    设置进程组ID
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
    pid_t pid;

    if((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }
    else if(pid == 0) {
        printf("child PID = %d\n", getpid());
        printf("child Group ID = %d\n", getpgid(0));     //返回组ID
        sleep(7);
        printf("----Group ID of child is changed to %d\n", getpgid(0));     //getpgid(0)参数传入0与getpgrp()作用相同，代表获取当前进程的进程组ID
        exit(0);
    }
    else if(pid > 0) {
        sleep(1);
        setpgid(pid, pid);      //让子进程自立门户，成为进程组组长,以它的pid作为进程组ID

        sleep(13);
        printf("\n");
        printf("parent PID = %d\n", getpid());
        printf("parent's parent process PID = %d\n", getppid());
        printf("parent Group ID = %d\n", getpgid(0));

        sleep(5);
        setpgid(getpid(), getppid());   //改变父进程的组ID作为父进程的父进程
        printf("\n------Group ID of parent is changed to %d\n", getpgid(0));

        while(1);
    }

    return 0;
}
