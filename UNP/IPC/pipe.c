//管道

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    int fd[2];
    pid_t pid;

    int ret = pipe(fd);
    if(ret == -1) {
        perror("pipe error:");
        exit(1);
    }

    pid = fork();
    
    if(pid == -1) {
        perror("pipe error:");
        exit(1);
    } 
    else if(pid == 0) {    //子进程读数据
        close(fd[1]);       //关闭写端下面读数据
        char buf[1024];
        ret = read(fd[0], buf, sizeof(buf));
        close(fd[0]);       //读完之后关闭读端
        if(ret == 0) {      //表示读到文件末尾了
            printf("\n");
        }
        write(STDOUT_FILENO, buf, ret);
    } 
    else {              //父进程写数据  写端是fd[1],读端是fd[0]
        close(fd[0]);   //关闭读端下面写数据
        write(fd[1], "Hello pipe\n", strlen("hello pipe\n"));
        close(fd[1]);   //写完之后关闭写端
        sleep(1);
    }

    return 0;
}