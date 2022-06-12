
//查看一个进程最多可以产生多少个子线程

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *tfn(void *arg){
    while(1)
    sleep(1);
}

int main(){
    pthread_t tid;
    int ret, count = 1;

    while(1)
    {
        ret = pthread_create(&tid, NULL, tfn, NULL);
        if(ret != 0){
            printf("%s\n", strerror(ret));
            break;
        }
        printf("---------%d\n", ++count);
    }
    


    return 0;
}