
//循环创建多个子线程


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>


void *thrd_func(void *arg) 
{
    // int i = *((int*)arg);
    int i = (int)arg;
    // sleep(i);
    printf("%dth thread: thread id = %lu, pid = %u\n", i + 1, pthread_self(), getpid());

    return NULL;
}

int main() 
{
    pthread_t tid;

    int i;
    for(i = 0; i < 5; i++) {
        int ret = pthread_create(&tid, NULL, thrd_func, (void *)i);
        if(ret != 0) {
            fprintf(stderr, "pthread_create error:%s\n", strerror(ret));
            exit(1);
        }
    }

    // sleep(i);
    pthread_exit(NULL);     //退出主控线程,其他线程要等待执行完成才能退出

    // return 0;   //这个return是将进程退出
}

/*
int main() {
    pthread_t tid;
    int i;

    for(i = 0; i < 5; i++) 
    {
        int *tmp = (int*)malloc(sizeof(int));
        *tmp = i;
    
        int res = pthread_create(&tid, NULL, thrd_func, (void*)tmp);
        if(res != 0) {
            perror("pthread_create error!\n");
            exit(1);
        }
        free(tmp);
    }

    // sleep(i);

    printf("parent thread id = %lu\n", pthread_self());
    pthread_exit(NULL);     //退出主控线程

    return 0;
}*/
