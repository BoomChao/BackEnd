/*
    将一个文件中内容利用read函数读取到另外一个文件中
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() 
{
    int fd = open("time.txt", O_RDONLY);
    if(fd == -1) {
        perror("open error");
        exit(1);
    }

    //创建一个新的文件，将"time.txt"中的内容读取到这个新创建的newfile.txt中去
    int fd2 = open("newfile.txt", O_CREAT | O_WRONLY, 0644);
    if(fd2 == -1) {
        perror("open error");
        exit(1);
    }

    char buf[2048];     //每次2Kb的读取
    int count = read(fd, buf, sizeof(buf));
    if(count == -1) {
        perror("read error");
        exit(1);
    }

    while(count)
    {
        //将存放在buf中的数据写入到另外一个文件当中
        int ret = write(fd2, buf, count);
        printf("write bytes %d\n", ret);
        count = read(fd, buf, sizeof(buf));
    }

    close(fd);
    close(fd2);

    return 0;
}
