

//回收多个子线程

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int var = 100;

void *tfn(void *arg)
{
    int i = (int)arg;
    // int i = *((int*)arg);

    sleep(i);
    if(i == 1) {
        var = 333;
        printf("var = %d\n", var);
        return (void*)var;
    }
    else if(i == 3) {
        var = 777;
        printf("I'm %dth pthread, pthread_id = %lu\n var = %d\n", i + 1, pthread_self(), var);
        pthread_exit((void*)var);
    }
    else {
        printf("I'm %dth pthread, pthread_id = %lu\n var = %d\n", i + 1, pthread_self(), var);
        pthread_exit((void*)var);
    }

    return NULL;
}

int main(void) {
    pthread_t tid[5];
    int i;
    int *ret[5];

    for(i = 0; i < 5; i++) {
        // int *tmp = (int*)malloc(sizeof(int));
        // *tmp = i;
        // pthread_create(&tid[i], NULL, tfn, (void*)tmp);
        pthread_create(&tid[i], NULL, tfn, (void*)i);
        // free(tmp);
    }

    for(i = 0; i < 5; i++) {
        pthread_join(tid[i], (void**)&ret[i]);
        // printf("----%d 's ret = %d\n", i, (int)ret[i]);
    }

    printf("I'm main pthread tid = %lu\t var = %d\n", pthread_self(), var);

    sleep(i);

    return 0;
}

