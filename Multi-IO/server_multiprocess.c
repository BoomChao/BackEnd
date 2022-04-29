#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>


int main()
{
    pid_t pid;
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
    addr.sin_addr.s_addr = htons(INADDR_ANY);

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
        cfd = accept(lfd, (struct sockaddr*)&cliaddr, &clilen);
        if(cfd == -1) {
            perror("accept");
            exit(0);
        }

        char ip[24]= {0};
        printf("client IP: %s, port: %d\n", inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, ip, sizeof(ip)), 
            ntohs(cliaddr.sin_port));
        
        pid = fork();

        if(pid < 0) {
            perror("fork");
            exit(0);
        }
        else if(pid == 0) {
            close(lfd);
            break;
        }
        else {
            close(cfd);
        }
    }

    if(pid == 0)
    {
        while(1)
        {
            char buf[1024];
            memset(buf, 0, sizeof(buf));
            int len = read(cfd, buf, sizeof(buf));
            if(len == 0) {
                close(cfd);
                return 0;
            } 
            else if(len > 0) {
                for(int i = 0; i < len; i++) {
                    buf[i] = toupper(buf[i]);
                }
                write(cfd, buf, len);
            }
            else {
                perror("error");
                exit(0);
            }
        }
    }

    return 0;
}