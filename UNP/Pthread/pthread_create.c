
//创建一个线程


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>


void *thrd_func(void *arg) 
{ 
    printf("In thread: thread id = %lu, pid = %u\n", pthread_self(), getpid());

    return NULL;
}

int main() {
    pthread_t tid;

    printf("In main1: thread id = %lu, pid = %u\n", pthread_self(), getpid());

    int ret = pthread_create(&tid, NULL, thrd_func, NULL);
    if(ret != 0) {
        fprintf(stderr, "pthread_create error:%s\n", strerror(ret));
        exit(1);
    }

    sleep(1);   
    printf("In main2: thread id = %lu, pid = %u\n", pthread_self(), getpid());

    pthread_exit(NULL);        //退出主控线程,子线程执行完毕才会退出

    return 0;
}