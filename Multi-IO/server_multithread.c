#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>

#define MAXLINE 8192
// #define SERV_PORT 8000

struct s_info {
    struct sockaddr_in cliaddr;
    int connfd;
};

void *do_work(void *arg)
{
    int n, i;
    struct s_info *ts = (struct s_info*)arg;
    char buf[MAXLINE];
    char str[INET_ADDRSTRLEN];

    while(1)
    {
        int len = read(ts->connfd, buf, MAXLINE);
        if(len == 0) {
            printf("the client %d closed...\n", ts->connfd);
            break;
        }

        for(int i = 0; i < len; i++) {
            buf[i] = toupper(buf[i]);
        }

        write(ts->connfd, buf, len);
    }

    close(ts->connfd);

    return (void*)0;
}


int main()
{
    pthread_t tid;
    struct s_info ts[256];
    int i = 0;

    int lfd, cfd;
    lfd = socket(AF_INET, SOCK_STREAM, 0);
    if(lfd == -1) {
        perror("socket");
        exit(0);
    }

    //设置端口复用
    int opt = 1;
    setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9999);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int res = bind(lfd, (struct sockaddr*)&addr, sizeof(addr));
    if(res == -1) {
        perror("bind");
        exit(0);
    }

    res = listen(lfd, 128);
    if(res == -1) {
        perror("listen");
        exit(0);
    }

    while(1)
    {
        struct sockaddr_in cliaddr;
        int clilen = sizeof(cliaddr);
        cfd = accept(lfd, (struct sockaddr*)&cliaddr, &clilen);  //阻塞等待客户端连接请求
        if(cfd == -1) {
            perror("accept");
            exit(0);
        }

        char ip[24]= {0};
        printf("client IP: %s, port: %d\n", inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, ip, sizeof(ip)), 
            ntohs(cliaddr.sin_port));

        ts[i].cliaddr = cliaddr;
        ts[i].connfd = cfd;

        //到达最大线程数,pthread_create出错处理,增加服务器稳定性
        pthread_create(&tid, NULL, do_work, (void*)&ts[i]);
        pthread_detach(tid);
        i++;
    }

    return 0;
}

