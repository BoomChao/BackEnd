/*
    创建守护进程
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>


//创建一个守护进程
void deamon()
{
    pid_t pid;

    pid = fork();

    if(pid > 0) {       //退出父进程
        exit(1);
    }

    setsid();   //将当前进程设置到一个新的回话组，当前进程既是进程组组长也是会话会长

    int ret = chdir("/home/chao/Documents/OS/Process/");
    if(ret < 0) {
        perror("chdir error");
        exit(1);
    }

    umask(0022);            //设置文件掩码,第一个0代表八进制;防止守护进程创建文件

    close(STDIN_FILENO);            //关闭0号文件描述符
    open("/dev/null", O_RDWR);      //打开一个文件时，默认0号文件描述符指向打开的文件
    dup2(0, STDOUT_FILENO);
    dup2(0, STDERR_FILENO);

}


// 守护进程执行函数
// 设置每隔3秒打印一下当前系统时间到文件中
void fun()
{
    time_t ts = 0;
    int line = 0;
    struct tm* tm = NULL;
    FILE *fp = NULL;
    fp = fopen("./time.txt", "w+");

    if(fp == NULL) {
        perror("fopen error");
        exit(1);
    }

    while(1)
    {
        ts = time(NULL);        
        if(ts == -1) {
            perror("get time error");
            exit(1);
        }

        tm = localtime(&ts);
        if(tm == NULL) {
            perror("local time error");
            exit(1);
        }

        // printf("%d %d %d %d %d %d \n", tm->tm_year+1900, tm->tm_mon, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);

        line++;

        //tm结构体里面的 tm.tm_year是默认减去1900的，所以实际年份要加上1900，tm.tm_mon也默认减去了1,所以实际月份也要加上1
        fprintf(fp, "%d %d %d %d %d %d\n", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);

        fflush(fp);

        sleep(3);

        if(line > 20) break;
    }
    
    fclose(fp);
}


int main()
{
    deamon();

    //守护进程主逻辑
    while(1) {
        fun();
    }

    return 0;
}
