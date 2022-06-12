
//父子进程共享打开的文件描述符---使用文件来完成进程间通信

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

int main()
{
    int fd1, fd2;
    pid_t pid;
    char buf[1024];
    char *str = "------test for shared fd in parent child process-----\n";

    pid = fork();
    if(pid < 0) 
    {
        perror("fork error");
        exit(1);
    }
    else if(pid == 0)  //子进程
    {   
        fd1 = open("test.txt", O_RDWR | O_CREAT);
        if(fd1 < 0){
            perror("open error");
            exit(1);
        }
        write(fd1, str, strlen(str));
        printf("child wrote over...\n");

    } 
    else    //父进程
    {    
        fd2 = open("test.txt", O_RDWR);
        if(fd2 < 0){
            perror("open errror");
            exit(1);
        }
        sleep(1);
        int len = read(fd2, buf, sizeof(buf));
        write(STDOUT_FILENO, buf, len);

        wait(NULL);
    }


    return 0;
}