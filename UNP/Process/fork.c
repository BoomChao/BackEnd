//创建子进程

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    pid_t pid;
    printf("XXXXXXX\n");

    pid = fork();
    if(pid == -1) {
        perror("fork error!");
        exit(1);
    }else if(pid == 0) {
        printf("I'm child, pid = %u, ppid = %u \n", getpid(), getppid());   //%u表示输出无符号(unsigned)整形数据,以十进制的形式输出
    }else {
        printf("I'm parent, pid = %u, ppid = %u \n", getpid(), getppid());
    }

    printf("YYYYYYY\n");

    return 0;
}
