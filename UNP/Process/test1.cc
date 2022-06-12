//回收子进程


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    pid_t pid;

    pid = fork();
    if(pid == -1){
        perror("fork error!");
        exit(1);
    }else if(pid == 0){
        printf("I'm child, pid = %u, ppid = %u \n", getpid(), getppid());   //%u表示输出无符号(unsigned)整形数据,以十进制的形式输出
        sleep(3);
        printf("I'm child, pid = %u, ppid = %u \n", getpid(), getppid());

    }else{
        sleep(1);
        printf("I'm parent, pid = %u, ppid = %u \n", getpid(), getppid());
    }


    return 0;
}
