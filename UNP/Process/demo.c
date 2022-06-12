

/*
void *tfn1(void *arg)
{
    printf("thread 1 returning\n");

    return (void*)111;
}

void *tfn2(void *arg)
{
    printf("thread 2 existing\n");

    pthread_exit((void*)222);
}

void *tfn3(void *arg)
{
    while(1) {
        pthread_testcancel();
        // printf("thread 3: I'm going to die in 3 seconds...\n");
        // sleep(1);
    }

    return (void*)666;
}

int main() {
    pthread_t tid;
    void *tret = NULL;

    pthread_create(&tid, NULL, tfn1, NULL);
    pthread_join(tid, &tret);
    printf("thread 1 exit code = %d\n\n", (int)tret);

    pthread_create(&tid, NULL, tfn2, NULL);
    pthread_join(tid, &tret);
    printf("thread 2 exit code = %d\n\n", (int)tret);

    pthread_create(&tid, NULL, tfn3, NULL);
    sleep(3);
    pthread_cancel(tid);
    pthread_join(tid, &tret);
    printf("thread 3 exit code = %d\n\n", (int)tret);

    return 0;
}



/*
int var = 100;

void *tfn(void *arg)
{
    int i;
    i = (int)arg;

    sleep(i);
    if(i == 1) {
        var = 333;
        printf("var = %d\n", var);
        return (void*)var;
    }
    else if(i == 3) {
        var = 777;
        printf("I'm %dth pthread, pthread_id = %lu\nvar = %d\n",i+1, pthread_self(), var);
        pthread_exit((void*)var);
    }
    else {
        printf("I'm %dth pthread, pthread_id = %lu\nvar = %d\n", i+1, pthread_self(), var);
        pthread_exit((void*)var);
    }

    return NULL;
}


int main(void)
{
    pthread_t tid[5];
    int i;
    int *ret[5];

    for(i = 0; i < 5; i++) {
        pthread_create(&tid[i], NULL, tfn, (void*)i);
    }

    for(i = 0; i < 5; i++) {
        pthread_join(tid[i], (void**)&ret[i]);
        printf("--------%d's ret = %d\n", i, (int)ret[i]);
    }

    printf("I'm main pthread tid = %lu\t var = %d\n", pthread_self(), var);

    sleep(i);

    return 0;
}



/*
typedef struct {
    int a;
    int b;
} exit_t;

void *tfn(void *arg)
{
    exit_t *ret;
    ret = malloc(sizeof(exit_t));

    ret->a = 100;
    ret->b = 300;

    pthread_exit((void*)ret);
}

int main(void) {
    pthread_t tid;
    exit_t *retval;

    pthread_create(&tid, NULL, tfn, NULL);

    //调用pthread_join可以获取线程退出状态
    pthread_join(tid, (void**)&retval);

    printf("a = %d, b = %d\n", retval->a, retval->b);

    return 0;
}








/*
int var = 100;

void *tfn(void *arg)
{
    var = 200;
    printf("thread\n");

    return NULL;
}

int main(void) {
    printf("At first var = %d\n", var);

    pthread_t tid;
    pthread_create(&tid, NULL, tfn, NULL);
    sleep(1);

    printf("after pthread_create, var = %d\n", var);

    return 0;
}
*/

/*
void *thrd_func(void *arg) 
{
    // int i = (int)arg;
    printf("In thread: thread id = %lu,pid = %u\n",pthread_self(), getpid());

    return NULL;
}

int main(int argc, char **argv) 
{
    pthread_t tid;
    int ret, i;

    // for(i = 0; i < 50; i++) {
    ret = pthread_create(&tid, NULL, thrd_func, NULL);
    if(ret != 0) {
        printf("pthread_create error\n");
        exit(1);
    }
    // } 

    // sleep(i);

    printf("In main2: thread id = %lu, pid = %u\n", pthread_self(), getpid());

    pthread_exit(NULL);
    
    return 0;
}


/*
int main(int argc, char **argv) {
    
    char *p = NULL;

    int fd = open("myTest.txt", O_CREAT|O_RDWR, 0644);

    if(fd < 0) {
        perror("open error!\n");
        exit(1);
    }

    int len = ftruncate(fd, 4);
    if(len == -1) {
        perror("ftruncate error!\n");
        exit(1);
    }

    p = mmap(NULL, 4, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0); 
    if(p == MAP_FAILED) {
        perror("map error!\n");
        exit(1);
    } 

    strcpy(p, "abc");   //写数据
    
    int ret = munmap(p, 4);
    if(ret == -1) {
        perror("mumap error!\n");
        exit(1);
    }
    close(fd);          //关闭文件


    return 0;
}
*/

/*
int var = 100;

int main(void) {
    int *p;
    pid_t pid;

    int fd;
    // fd = open("temp", O_RDWR|O_CREAT|O_TRUNC, 0644);
    fd = open("/dev/zero", O_RDWR);
    // if(fd < 0) {
    //     perror("open error\n");
    //     exit(1);
    // }

    // unlink("temp");
    // ftruncate(fd, 4);

    // p = (int*)mmap(NULL, 4, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    // p = (int*)mmap(NULL, 4, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0);
    p = (int*)mmap(NULL, 4, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0);
    
    if(p == MAP_FAILED) {
        perror("mmap error\n");
        exit(1);
    }

    close(fd);      //映射区建立完毕即可关闭文件

    pid = fork();
    if(pid == 0) {
        *p = 2000;
        var = 1000;
        printf("child, *p = %d, var = %d\n", *p, var);
    }
    else {
        sleep(1);
        printf("parent, *p = %d, var = %d\n", *p, var);
        wait(NULL);

        int ret = munmap(p, 4);     //释放映射区
        if(ret == -1) {
            perror("munmap error\n");
            exit(1);
        }
    }

    return 0;
}

*/


// int main() {
//     printf("hello world\n");

//     return 0;
// }

/*


struct msg {
    struct msg *next;
    int num;
};


struct msg *head = NULL;
// struct msg *mp = NULL;

pthread_cond_t has_producted = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *consumer(void *arg)
{
    int n = 0;
    while(n++ < 10)
    {
        //加锁
        pthread_mutex_lock(&lock);

        while(head == NULL) {
            pthread_cond_wait(&has_producted, &lock);
        }

        struct msg *tmp = head;
        head = tmp->next;

        pthread_mutex_unlock(&lock);

        printf("--Consumer -- %d\n", tmp->num);
        free(tmp);
        sleep(rand()%3);
    }

}

void *producer(void *arg)
{
    int n = 0;
    while(n++ < 10)
    {
        //生产数据生产数据，消费数据
        struct msg *mp = (struct msg*)malloc(sizeof(struct msg));
        mp->num = rand()%100 + 1;
        printf("--Produce -- %d\n", mp->num);

        //将数据放到共享区域
        pthread_mutex_lock(&lock);
        mp->next = head;
        head = mp;
        pthread_mutex_unlock(&lock);

        //通知消费者
        pthread_cond_signal(&has_producted);
        sleep(rand()%3);
    }

}

int main()
{
    pthread_t tid_prod, tid_cons;

    pthread_create(&tid_prod, NULL, producer, NULL);
    pthread_create(&tid_cons, NULL, consumer, NULL);

    pthread_join(tid_prod, NULL);
    pthread_join(tid_cons, NULL);

    return 0;
}
*/



// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>


// unsigned int mysleep(unsigned int seconds);


// int main() {
//     alarm()
//     pause();   


//     return 0;
// }

// unsigned int mysleep(unsigned int seconds)
// {
//     struct sigaction act, oldact;
//     int ret = sigaction(SIGALRM, &act, &oldact);

//     alarm(seconds);
//     pause();     //造成当前进程主动挂起,等待信号将其唤醒

//     return ;
// }

// void catch_signalarm(int signo)
// {

// }
/*
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() 
{
    // time_t ts = 0;

    // ts = time(NULL);

    // printf("%lu\n", ts);

    // struct tm* tm = localtime(&ts);

    // printf("%d", tm->tm_year);

    // int fd = open("myhello", O_RDWR | O_CREAT, 0644);
    // if(fd == -1) {
    //     perror("open file");
    //     exit(1);
    // }

    // int ret = close(fd);
    // if(ret == -1) {
    //     perror("close file");
    //     exit(1);
    // }

    int fd = open("time.txt", O_RDONLY);

    if(fd == -1) {
        perror("open");
        exit(1);
    }

    int fd1 = open("newfile", O_CREAT | O_WRONLY, 0664);

    char buf[2048];

    int count = read(fd, buf, sizeof(buf));
    if(count == -1) {
        perror("read");
        exit(1);
    }

    while(count)
    {
        //将读出的数据写入到另外一个文件中
        int ret = write(fd1, buf, count);
        printf("write bytes %d\n", ret);
        count = read(fd, buf, sizeof(buf));
    }

    close(fd);
    close(fd1);

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM 5

int queue[NUM];

sem_t blank_number, product_number;

void *producr(void *arg)
{
    int i = 0;

    while(1)
    {
        sem_wait(&blank_number);
        queue[i] = rand()%100 + 1;
        printf("Prouduce---%d\n", queue[i]);
        sem_post(&product_number);

        i = (i + 1)%NUM;
        sleep(rand()%3);
    }

}


void *consumer(void *arg)
{
    int i = 0;

    while(1)
    {
        sem_wait(&product_number);
        queue[i] = rand()%100 + 1;
        printf("Consumer--%d\n", queue[i]);
        sem_post(&blank_number);

        i = (i + 1)%NUM;
        sleep(rand()%3);
    }

}

int main()
{
    pthread_t pid, tid;

    sem_init(&blank_number, 0, NUM);
    sem_init(&product_number, 0, 0);

    pthread_create(&pid, NULL, producr, NULL);
    pthread_create(&tid, NULL, consumer, NULL);

    pthread_join(pid, NULL);
    pthread_join(tid, NULL);

    sem_destroy(&blank_number);
    sem_destroy(&product_number);

    return 0;
}

#define N 10

semaphore mutex = 1;
semaphore emptyBuffer = N;
semaphore fullBuffer = 0;

void producer()
{
    while(1)
    {
        p(emptyBuffer);
        p(mutex);
        
        //将生产的数据放到缓冲区

        v(mutex);
        v(fullBuffer);
    }
}

void consumer()
{
    while(1)
    {
        p(fullBuffer);
        p(mutex);

        //从缓冲区拿数据

        v(mutex);
        v(emptyBuffer);
    }
}
*/

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
        sem_wait(&blank_number);
        queue[i] = rand()%100 + 1;
        printf("---Produce--%d\n", queue[i]);
        sem_post(&product_number);

        i = (i + 1)%NUM;
        sleep(rand()%3);
    }

}

void *consumer(void *arg)
{
    int i = 0;

    while(1)
    {
        sem_wait(&product_number);
        printf("---Consume--%d\n", queue[i]);
        queue[i] = 0;
        sem_post(&blank_number);

        i = (i + 1)%NUM;
        sleep(rand()%3);
    }

}

int main() {

    pthread_t tid1, tid2;

    sem_init(&blank_number, 0, NUM);
    sem_init(&product_number, 0, 0);

    pthread_create(&tid1, NULL, producer, NULL);
    pthread_create(&tid2, NULL, consumer, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    sem_destroy(&blank_number);
    sem_destroy(&product_number);

    // pthread_join(tid1, NULL);
    // pthread_join(tid2, NULL);

    // sem_destroy(&blank_number);
    // sem_destroy(&product_number);

    return 0;
}
