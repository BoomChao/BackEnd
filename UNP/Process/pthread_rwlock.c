
/*
    读写锁
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int counter;            //全局资源
pthread_rwlock_t rwlock;

void* th_write(void *arg)
{ 
    int t;
    int i = (int)arg;

    while(1) 
    {
        t = counter;
        usleep(1000);

        pthread_rwlock_wrlock(&rwlock);
        printf("====write %d : %lu counter = %d ++counter = %d\n", i, pthread_self(), t, ++counter);
        pthread_rwlock_unlock(&rwlock);

        usleep(5000);
    }

    return NULL;
}

void* th_read(void *arg)
{
    int i = (int)arg;

    while(1) 
    {
        pthread_rwlock_rdlock(&rwlock);
        printf("---------read %d : %lu %d\n", i, pthread_self(), counter);
        pthread_rwlock_unlock(&rwlock);

        usleep(900);
    } 

    return NULL;
}


int main() 
{
    int i;
    pthread_t tid[8];

    pthread_rwlock_init(&rwlock, NULL);

    for(i = 0; i < 3; i++) {
        pthread_create(&tid[i], NULL, th_write, (void*)i);      //3个线程写
    }

    for(i = 0; i < 5; i++) {
        pthread_create(&tid[i+3], NULL, th_read, (void*)i);     //5个线程读
    }

    sleep(3);
    for(i = 0; i < 8; i++) {
        pthread_cancel(tid[i]);
        pthread_join(tid[i], NULL);     //回收子线程
    }

    pthread_rwlock_destroy(&rwlock);      //销毁读写锁

    return 0;
}
