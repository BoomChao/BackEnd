
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

// void *thread_function(void *arg) {
//     printf("thread_function is running, Argument is %s\n", (char*)arg);
// }

// char message[] = "hello world";

// int main() {
//     int res;
//     pthread_t a_thread;
//     int i = 0;

//     while(1)
//     {
//         res = pthread_create(&a_thread, NULL, thread_function, (void*)message);
//         i++;

//         if(res != 0) {
//             printf("线程个数 %d", i);
//             perror("Thread creation failed!\n");
//             return 0;
//         }

//     }

//     return 0;
// }


// int var = 0;


// int main() {
//     pid_t pid;

//     pid = fork();

//     if(pid == -1) {
//         perror("Error!\n");
//     }
//     else if(pid > 0) {
//         sleep(1);
//         printf("parent\n");
//     }
//     else {
//         execlp("ls", "ls", "-l", "-h", NULL);
//     }

//     return 0;
// }

/*
int main(void) {
    int fd;

    fd = open("ps.out", O_WRONLY|O_CREAT|O_TRUNC, 0644);
    // printf("%d\n", fd);
    if(fd < 0) {
        perror("open error!\n");
        exit(1);
    }

    dup2(fd, STDOUT_FILENO);

    execlp("ps", "ps", "ax", NULL);

    return 0;
}
*/
/*

int main() {
    int fd[2];
    pid_t pid;

    int ret = pipe(fd);
    if(ret == -1) {
        perror("pipe error!\n");
        exit(1);
    }

    pid = fork();
    if(pid == -1) {
        perror("pipe error!\n");
        exit(1);
    }
    else if(pid == 0) { //子进程
        close(fd[1]);
        char buf[1024];
        ret = read(fd[0], buf, sizeof(buf));
        
        if(ret == 0) {      //读到文件末尾就会读到0
            printf("---\n");
        }

        write(STDOUT_FILENO, buf, ret);
    }
    else {  //父进程
        sleep(3);

        close(fd[0]);
        // char *str = "hello pipe\n";
        // write(fd[1], "hello pipe\n", strlen("hello pile\n"));
    }

    return 0;
}
*/
/*
struct STU {
    int id;
    char name[20];
    char sex;
};


void sys_err(const char *str) 
{
    perror(str);
    exit(1);
}

/*
    读
*/
/*
int main(int argc ,char *argv[]) {
    int fd;
    struct STU student;
    struct STU *mm;

    if(argc < 2) {
        printf("./a.out file_shared\n");
        exit(-1);
    }
    fd = open(argv[1], O_RDONLY);
    if(fd == -1) {
        sys_err("open error\n");
    }

    mm = mmap(NULL, sizeof(student), PROT_READ, MAP_SHARED, fd, 0);
    if(mm == MAP_FAILED) {
        sys_err("mmap error!\n");
    }

    close(fd);

    while(1) {
        printf("id = %d\tname = %s\t%c\n", mm->id, mm->name, mm->sex);
        sleep(2);
    }

    munmap(mm, sizeof(student));

    return 0;
}

*/

int main()
{
    time_t ts = 0;
    int line = 0;
    struct tm* tm = NULL;
    FILE *fp = NULL;
    fp = fopen("./time.txt", "w+");

    if(fp == NULL) {
        perror("fopen error");
        exit(1);
    }

    while(1)
    {
        ts = time(NULL);        
        if(ts == -1) {
            perror("get time error");
            exit(1);
        }

        tm = localtime(&ts);
        if(tm == NULL) {
            perror("local time error");
            exit(1);
        }

        printf("%d %d %d %d %d %d \n", tm->tm_year+1900, tm->tm_mon, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);

        line++;

        fprintf(fp, "%d %d %d %d %d %d\n", tm->tm_year+1900, tm->tm_mon, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);

        fflush(fp);

        sleep(1);

        if(line > 20) break;
    }
    
    fclose(fp);

    return 0;
}
