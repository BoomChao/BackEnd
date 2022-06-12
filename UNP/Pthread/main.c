
/*
    这个用来测试的
*/

//创建单个子线程

/*


void *thrd_func(void *arg)
{
    int n = *((int*)arg);
    // sleep(n);
    printf("I'm %d thread: thread id = %lu, pid = %u\n", n + 1, pthread_self(), getpid());
}

int main() {
    pthread_t tid;
    int i;

    for(i = 0; i < 5; i++) {
        // int *tmp = (int*)malloc(sizeof(int));
        // *tmp = i;
        int tmp = i;
        int ret = pthread_create(&tid, NULL, thrd_func, (void*)&tmp);

        if(ret != 0) {
            perror("create error!");
            exit(1);
        }

        sleep(1);
        // free(tmp);
    }

    // sleep(i);

    printf("In main : thread_id = %lu, pid = %u\n", pthread_self(), getpid());

    return 0;
}
*/

#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void* thread_func(void *arg) 
{
    printf("%lu  %u \n", pthread_self(), getpid());

    sleep(2);

    return NULL;
}

int main() {
    pthread_t tid;

    int ret = pthread_create(&tid, NULL, thread_func, NULL);
    if(ret != 0) {
        fprintf(stderr, "%s\n", strerror(ret));
        exit(1);
    }

    // sleep(1);
    // pthread_join(tid, NULL);
    pthread_exit(NULL);

    return 0;
}

 