
/*
    信号量实现生产者和消费者问题
*/


//信号量实现线程间同步

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM 5

int queue[NUM];

sem_t blank_number, product_number;

void *producer(void *arg)
{
    int i = 0;

    while(1)
    {
        sem_wait(&blank_number);            //将空格数--; 如果信号量>0,则信号量--,信号量=0,则造成线程阻塞(因为信号量不能为负值)
        queue[i] = rand()%100 + 1;
        printf("---Produce--%d\n", queue[i]);
        sem_post(&product_number);          //将产品数++

        i = (i + 1)%NUM;        //模拟环形队列,下一次再生产就放在(i+1)的位置上
        sleep(rand()%3);
    }

}

void *consumer(void *arg)
{
    int i = 0;

    while(1)
    {
        sem_wait(&product_number);
        printf("--Consume--%d\n", queue[i]);
        queue[i] = 0;
        sem_post(&blank_number);

        i = (i + 1)%NUM;
        sleep(rand()%3);
    }

}


int main(int argc, char *argv[])
{
    pthread_t tid1, tid2;

    //num代表信号初始化的值
    sem_init(&blank_number, 0, NUM);
    sem_init(&product_number, 0, 0);

    pthread_create(&tid1, NULL, producer, NULL);
    pthread_create(&tid2, NULL, consumer, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    sem_destroy(&blank_number);
    sem_destroy(&product_number);

    return 0;
}
