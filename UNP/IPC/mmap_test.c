
//mmap创建映射区

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>


int main() 
{
    int len, ret;
    char *p = NULL;
    int fd = open("mytest.txt", O_CREAT|O_RDWR, 0644);
    if(fd < 0) {
        perror("open error");
        exit(1);
    }

    len = ftruncate(fd, 4);  //将文件截断为指定长度

    if(len == -1){
        perror("ftruncate error:");
        exit(1);
    }

    p = mmap(NULL, 4, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    
    if(p == MAP_FAILED) {
        perror("mmap error");
        exit(1);
    }
    strcpy(p, "abc\n");    //写入字符串

    ret = munmap(p, 4);    //文件描述符先关闭对mmap没有影响,因为操作文件的不再是通过文件描述符了,是直接通过地址的方式
    if(ret == -1) {
        perror("munmap error:");
        exit(1);
    }

    close(fd);

    return 0;
}