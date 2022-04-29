#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
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

    int maxfd = lfd;
    fd_set rdset, rdtemp;

    FD_ZERO(&rdset);
    FD_SET(lfd, &rdset);

    while(1)
    {
        //3.使用select来监听
        rdtemp = rdset;
        int num = select(maxfd+1, &rdtemp, NULL, NULL, NULL);

        //判断是否有新连接(监听的文件描述符上有读事件说明有客户端需要建立连接)
        if(FD_ISSET(lfd, &rdtemp))
        {
            struct sockaddr_in cliaddr;
            int cliLen = sizeof(cliaddr);

            //这里调用accept就不会再阻塞了
            int cfd = accept(lfd, (struct sockaddr*)&cliaddr, &cliLen);

            FD_SET(cfd, &rdset);
            maxfd = cfd > maxfd ? cfd : maxfd;  //重置最大的文件描述符
        }

        //没有新连接，通信
        for(int i = 0; i < maxfd+1; i++)
        {
            if(i != lfd && FD_ISSET(i, &rdtemp))
            {
                char buf[10] = {0};

                int len = read(i, buf, sizeof(buf));
                if(len == 0) {
                    printf("client closed...\n");
                    FD_CLR(i, &rdset);
                    close(i);
                }
                else if(len > 0) {
                    //收到数据,大小写转换
                    for(int i = 0; i < len i++) {
                        buf[i] = toupper(buf[i]);
                    }
                    write(i, buf, len);
                }
                else {
                    //异常
                    perror("read");
                }
            }
        }

    }

    close(lfd);

    return 0;
}