//exec函数族

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid;
    pid = fork();

    if(pid == -1) {
        perror("fork error");
        exit(1);
    } else if(pid > 0) {    //父进程
        sleep(1);
        printf("parent\n");
    } else {                //子进程
        // execlp("ls", "ls", "-l", "-a", NULL);
        execlp("ls", "ls", "-lh", (char*)0);    //第二个参数之后(第三个参数开始就是传给可执行文件的参数)
    }

    return 0;
}