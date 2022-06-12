

/*
    进程间同步(利用互斥锁)
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/mman.h>
#include <sys/wait.h>

struct mt {
    int num;
    pthread_mutex_t mutex;          //锁
    pthread_mutexattr_t mutexattr;  //锁对应的属性
};

int main() {
    int i;
    struct mt *mm;
    pid_t pid;

    mm = mmap(NULL, sizeof(*mm), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANON, -1, 0);
    memset(mm, 0, sizeof(*mm));

    pthread_mutexattr_init(&mm->mutexattr);
    pthread_mutexattr_setpshared(&mm->mutexattr, PTHREAD_PROCESS_SHARED);       //修改属性为进程间共享

    pthread_mutex_init(&mm->mutex, &mm->mutexattr);

    pid = fork();
    if(pid == 0) {      //子进程返回0
        for(i = 0; i < 10; i++) {
            pthread_mutex_lock(&mm->mutex);
            (mm->num)++;
            printf("--child ---- num++ %d\n", mm->num);
            pthread_mutex_unlock(&mm->mutex);
            // sleep(1);
        }
    }
    else if(pid > 0) {
        for(i = 0; i < 10; i++) {
            // sleep(1);
            pthread_mutex_lock(&mm->mutex);
            mm->num += 2;
            printf("--parent-- num+=2 %d\n", mm->num);
            pthread_mutex_unlock(&mm->mutex);
        }

        wait(NULL);     //阻塞回收子进程
    }

    pthread_mutexattr_destroy(&mm->mutexattr);
    pthread_mutex_destroy(&mm->mutex);
    munmap(mm, sizeof(*mm));

    return 0;
}