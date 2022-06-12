
//非血缘关系的两个进程完成进程间通信

/*
    写进程
*/

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>

struct STU {
    int id;
    char name[20];
    char sex;
};

void sys_err(char *str){
    perror(str);
    exit(-1);
}


int main(int argc, char *argv[])
{
    // int fd;
    struct STU studnet;
    // struct STU *mm;

    // if(argc < 2){
    //     printf("./a.out file_shared\n");
    //     exit(1);
    // }

    int fd = open("mytest.txt", O_RDONLY);
    if(fd == -1) {
        sys_err("open error");
    }

    struct STU *mm = mmap(NULL, sizeof(studnet), PROT_READ, MAP_SHARED, fd, 0);
    if(mm == MAP_FAILED)  {
        sys_err("mmap error");
    }

    unlink("tmp");

    close(fd);

    while(1){
        printf("id = %d\t name = %s\t %c\n", mm->id, mm->name, mm->sex);
        sleep(2);
    }

    munmap(mm, sizeof(studnet));

    return 0;
}