//僵尸进程

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    pid_t pid, wpid;
    int status;
    pid = fork();

    if(pid == 0){
        printf("--child, my parent = %d, going to sleep 3s\n", getppid());
        sleep(3);
        printf("----child die-----\n");
        // exit(76);
        return 100;
    }else if(pid > 0){
        wpid = wait(&status);     //阻塞等待子进程结束后回收
        if(wpid == -1){    
            perror("wait error");
            exit(1);
        }
        if(WIFEXITED(status)){
            printf("child exit with %d\n", WEXITSTATUS(status));
        }
        if(WIFSIGNALED(status)){
            printf("child killd by %d\n", WTERMSIG(status));
        }

        while(1){
            printf("I'm parent, pid = %d, myson = %d\n", getpid(), pid);
            sleep(1);
        }
    }else{
        perror("fork");
        return 1;
    }


    return 0;
}