


// int main()
// {
//     int fd[2];
//     pid_t pid;

//     pipe(fd);

//     pid = fork();

//     if(pid == 0) {
//         // sleep(1);   //保证父进程能够写入数据
//         close(fd[1]);
//         char buf[1024];
//         int res = read(fd[0], buf, sizeof(buf));
//         if(res == 0) {
//             printf("\n");
//         }
//         write(STDOUT_FILENO, buf, res);
//     }
//     else {
//         // sleep(3);
//         close(fd[0]);
//         write(fd[1], "hello pipe\n", strlen("hello pipe\n"));
//         sleep(1);
//     }

//     return 0;
// }

// int main()
// {
//     int fd[2];
//     int ret, i;
//     pid_t pid;

//     ret = pipe(fd);
    
//     for(i = 0; i < 2; i++) 
//     {
//         pid = fork();
//         if(pid == 0) break;
//     }

//     if(i == 2) {
//         close(fd[0]);
//         close(fd[1]);
//         wait(NULL);
//         wait(NULL);
//     }
//     else if(i == 0) {   //兄进程
//         close(fd[0]);
//         dup2(fd[1], STDOUT_FILENO);
//         execlp("ls", "ls", NULL);
//     }
//     else if(i == 1) {   //子进程
//         close(fd[1]);
//         dup2(fd[0], STDIN_FILENO);
//         execlp("wc", "wc", "-l", NULL);
//     }

//     return 0;
// }

/*
int main()
{
    char buf[4096];

    int ret = mkfifo("mytestfifo", 0644);

    int fd = open("mytestfifo", O_WRONLY);

    while(1)
    {
        sprintf(buf, "hello itcast\n");
        write(fd, buf, strlen(buf));
    }

    close(fd);

    return 0;
}
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int var = 100;

int main() 
{
    // int fd = open("temp", O_RDWR|O_CREAT|O_TRUNC, 0644);
    // if(fd < 0) {
    //     perror("open error\n");
    //     exit(1);
    // }

    // unlink("temp");             //删除临时文件目录项,使之具备被释放条件,当所有使用该文件的进程结束后,该文件被自动释放
    // ftruncate(fd, 4);

    // int fd = open("/dev/zero", O_RDWR);

    int *p = (int*)mmap(NULL, 4, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANON, -1, 0);
    if(p == MAP_SHARED) {
        perror("mmap error\n");
        exit(1);
    }

    // close(fd);      //映射区创建完毕,即可关闭文件描述符

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