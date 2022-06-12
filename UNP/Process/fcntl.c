
/*
    使用文件锁来进行进程间同步
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void sys_err(char *str) {
    perror(str);
    exit(1);
}

int main(int argc, char *argv[]) {
    int fd;
    struct flock f_lock;

    if(argc < 2) {
        printf("./a.out filename\n");
        exit(1);
    }

    if((fd = open(argv[1], O_RDWR)) < 0) {
        sys_err("open");
    }

    f_lock.l_type = F_WRLCK;        //选用写锁
    // l_lock.l_type = F_RDLCK;

    f_lock.l_whence = SEEK_SET;
    f_lock.l_start = 0;
    f_lock.l_len = 0;       //0表示将整个文件加锁

    fcntl(fd, F_SETLKW, &f_lock);
    printf("get flock\n");

    sleep(5);

    f_lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLKW, &f_lock);
    printf("un lock\n");

    close(fd);

    return 0;
}

