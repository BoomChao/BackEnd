#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/epoll.h>
#include <ctype.h>


int main()
{
    //1.创建监听的socket
    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    if(lfd == -1) {
        perror("socket error");
        exit(0);
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(9999);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    //设置端口复用
    int opt = 1;
    setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    //2.绑定IP地址和端口
    int res = bind(lfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if(res == -1) {
        perror("bind error");
        exit(0);
    }

    res = listen(lfd, 64);
    if(res == -1) {
        perror("listen error");
        exit(0);
    }

    //创建一个epoll模型
    int epfd = epoll_create(100);
    if(epfd == -1) {
        perror("epoll_create");
        exit(0);
    }

    //往epoll实例中添加需要检测的节点，现在只有监听的文件描述符
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = lfd;
    res = epoll_ctl(epfd, EPOLL_CTL_ADD, lfd, &ev);
    if(res == -1) {
        perror("epoll_ctl");
        exit(0);
    }

    struct epoll_event evs[1024];
    int size = sizeof(evs)/sizeof(struct epoll_event);

    while(1)
    {
        //3.使用epoll进行监听(就是检查创建的epoll实例中有没有就绪的文件描述符)
        int num = epoll_wait(epfd, evs, size, -1);

        for(int i = 0; i < num; i++)
        {
            int curfd = evs[i].data.fd;
            
            //建立新连接
            if(curfd == lfd) 
            {
                int cfd = accept(curfd, NULL, NULL);
                ev.events = EPOLLIN;                //这里默认就是水平触发
                // ev.events = EPOLLIN | EPOLLET;   //这样就是设定为边沿触发
                ev.data.fd = cfd;

                //将得到的文件描述符添加到epoll模型中，下一轮循环的时候就可以被检测到了
                res = epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &ev);
                if(res == -1) {
                    perror("epoll_ctl-accept");
                    exit(0);
                }
            }
            else 
            {
                char buf[1024];
                memset(buf, 0, sizeof(buf));
                int len = recv(curfd, buf, sizeof(buf), 0);
                
                if(len == 0) {
                    printf("client closed...");
                    epoll_ctl(epfd, EPOLL_CTL_DEL, curfd, NULL);
                    close(curfd);
                }
                else if(len > 0) {
                    for(int i = 0; i < len; i++) {
                        buf[i] = toupper(buf[i]);
                    }
                    send(curfd, buf, len, 0);
                }
                else {
                    perror("recv");
                    exit(0);
                }
            }
        }

    }

    return 0;
}