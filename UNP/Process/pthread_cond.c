
/*
    借助条件变量模拟生产者和消费者问题
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

struct msg {
    struct msg *next;
    int num;
};

struct msg *head = NULL;
// struct msg *mp = NULL;       //视频上是错误的,像视频上那么写操作的mp很有可能是producer正在生成的mp,而不是consumer的mp

//静态初始化 一个条件变量与互斥量
pthread_cond_t has_producted = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *consumer(void *p)
{
    while(1)
    {
        pthread_mutex_lock(&lock);
        while(head == NULL) {                           //while循环用来处理存在多个消费者的情况,保证每次只有一个消费者消费
            pthread_cond_wait(&has_producted, &lock);   //判断条件变量是否满足,不满足则放弃锁阻塞等待
        }

        struct msg *mp = head;
        head = mp->next;

        pthread_mutex_unlock(&lock);

        printf("--Consumer -- %d\n", mp->num);
        free(mp);
        sleep(rand()%5);
    }

}


void *producer(void *p)
{
    while(1)
    {
        struct msg *mp = (struct msg*)malloc(sizeof(struct msg));
        mp->num = rand()%100 + 1;           //模拟生产一个产品
        printf("--Produce -- %d\n", mp->num);

        pthread_mutex_lock(&lock);
        mp->next = head;
        head = mp;
        pthread_mutex_unlock(&lock);

        pthread_cond_signal(&has_producted);
        sleep(rand()%5);                    //这个循环模拟CPU易主
    }

}


int main(int argc, char *argv[])
{
    pthread_t pid, cid;

    srand(time(NULL));

    pthread_create(&pid, NULL, producer, NULL);
    pthread_create(&cid, NULL, consumer, NULL);

    // sleep(20);  //20s后结束
    
    // pthread_cancel(pid);
    // pthread_cancel(cid);

    pthread_join(pid, NULL);    //主控线程回收这两个子线程
    pthread_join(cid, NULL);

    return 0;
}

