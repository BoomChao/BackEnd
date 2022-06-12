
//线程共享全局变量


#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int var = 100;

void *fun(void *arg) 
{
    var = 200;
    printf("thread\n");

    return NULL;
}


int main(){
    printf("At first var = %d\n", var);

    pthread_t tid;
    pthread_create(&tid, NULL, fun, NULL);
    sleep(1);

    printf("After pthread_create, var = %d\n", var);

    return 0;
}
