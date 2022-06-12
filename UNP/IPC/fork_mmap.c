
/*
    利用共享内存进行进程间通信
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

int var = 100;

int main() 
{
    int fd = open("temp", O_RDWR|O_CREAT|O_TRUNC, 0644);
    if(fd < 0) {
        perror("open error\n");
        exit(1);
    }

    unlink("temp");             //删除临时文件目录项,使之具备被释放条件,当所有使用该文件的进程结束后,该文件被自动释放
    ftruncate(fd, 4);

    int *p = (int*)mmap(NULL, 4, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if(p == MAP_FAILED) {
        perror("mmap error\n");
        exit(1);
    }

    close(fd);      //映射区创建完毕,即可关闭文件描述符

    pid_t pid = fork();
    if(pid == 0) {
        *p = 2000;
        var = 1000;
        printf("child, *p = %d, var = %d\n", *p, var);
    } 
    else {
        sleep(1);
        printf("parent, *p = %d, var = %d\n", *p, var);
        wait(NULL);

        int res = munmap(p, 4);
        if(res == -1) {
            perror("mumap error\n");
            exit(1);
        }
    }

    return 0;
}