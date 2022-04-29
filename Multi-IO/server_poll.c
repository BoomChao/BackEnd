#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <poll.h>
#include <ctype.h>

int main()
{
    //1.创建一个socket
    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    if(lfd == -1) {
        perror("create socket");
        exit(0);
    }

    //2.绑定IP地址和端口
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9999);
    addr.sin_addr.s_addr = INADDR_ANY;
    int res = bind(lfd, (struct sockaddr*)&addr, sizeof(addr));
    if(res == -1) {
        perror("bind");
        exit(0);
    }

    res = listen(lfd, 128);   //这不是监听(这是设定能够同时和服务端建立连接的最大上限数)
    if(res == -1) {
        perror("listen");
        exit(0);
    }

    //创建自定义的文件描述符集合
    struct pollfd fds[1024];
    for(int i = 0; i < 1024; i++) {     //初始化
        fds[i].fd = -1;
        fds[i].events = POLLIN;
    }
    fds[0].fd = lfd;

    int maxfd = lfd;
    
    while(1)
    {
        //3.使用poll监听
        res = poll(fds, maxfd + 1, -1);
        if(res == -1) {
            perror("poll");
            exit(0);
        }

        //有新连接
        if(fds[0].revents & POLLIN) 
        {
            struct sockaddr_in sockcli;
            int len = sizeof(sockcli);

            //这里调用accept就不会再阻塞了
            int connfd = accept(lfd, (struct sockaddr*)&sockcli, &len);
            
            int i = 0;
            for(; i < 1024; i++) {
                if(fds[i].fd == -1) {
                    fds[i].fd = connfd;
                    break;
                }
            }
            maxfd = i > maxfd ? i : maxfd;
        }

        //通信,有客户端发送数据过来
        for(int i = 1; i <= maxfd; i++)
        {
            if(fds[i].revents & POLLIN) 
            {
                char buf[128];
                int len = read(fds[i].fd, buf, sizeof(buf));

                if(len == 0) {
                    printf("client closed...");
                    close(fds[i].fd);
                    fds[i].fd = -1;
                }
                else if(len > 0) {
                    for(int i = 0; i < len; i++) {
                        buf[i] = toupper(buf[i]);
                    }
                    write(fds[i].fd, buf, len);
                }
                else {
                    perror("read");
                    // exit(0);
                }
            }
        }

    }

    //这个其实用不到，服务端永远不会关闭
    close(lfd);

    return 0;
}

