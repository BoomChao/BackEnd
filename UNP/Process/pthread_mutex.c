
/*
    互斥锁
*/

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex;      //父子线程共享全局变量

void* tfn(void *arg)
{
    srand(time(NULL));

    while(1) 
    {
        pthread_mutex_lock(&mutex);     //加锁
        
        printf("hello ");
        sleep(rand()%3);
        printf("world\n");
        // pthread_mutex_lock(&mutex);     //死锁

        pthread_mutex_unlock(&mutex);   //解锁

        sleep(rand()%3);        
    }

    return NULL;
}


int main() 
{
    int flag = 5;

    pthread_t tid;
    srand(time(NULL));

    pthread_mutex_init(&mutex, NULL);     //初始化完成后mutex的值为1

    pthread_create(&tid, NULL, tfn, NULL);

    while(flag--) 
    {
        pthread_mutex_lock(&mutex);     //加锁
        
        printf("HELLO ");
        sleep(rand()%3);
        printf("WORLD\n");

        pthread_mutex_unlock(&mutex);   //解锁

        sleep(rand()%3);
    }

    pthread_mutex_destroy(&mutex);

    pthread_cancel(tid);    //杀死线程
    pthread_join(tid, NULL);

    return 0;
}


