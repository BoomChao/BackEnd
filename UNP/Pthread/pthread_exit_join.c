
//回收子线程

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
    int a;
    int b;
} exit_t;


void *tfn(void *arg) 
{
    exit_t *ret;
    ret = (exit_t*)malloc(sizeof(exit_t));

    ret->a = 100;
    ret->b = 300;

    pthread_exit((void*)ret);

    return 0;
}


int main() {
    pthread_t tid;
    exit_t *retval;

    pthread_create(&tid, NULL, tfn, NULL);

    //pthread_join可以获取线程的退出状态
    pthread_join(tid, (void**)&retval);                 //等价于进程中的wait函数
    printf("a = %d, b = %d\n", retval->a, retval->b);

    return 0;
}
