#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>

int main()
{
    //1.创建一个socket
    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    if(lfd == -1) {
        perror("socket");
        exit(0);
    }

    //2.绑定IP和端口
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9999);
    addr.sin_addr.s_addr = INADDR_ANY;

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

    struct sockaddr_in cliaddr;
    int clilen = sizeof(cliaddr);
    int cfd = accept(lfd, (struct sockaddr*)&cliaddr, &clilen);
    if(cfd == -1) {
        perror("accept");
        exit(0);
    }

    char ip[24]= {0};
    printf("client IP: %s, port: %d\n", inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, ip, sizeof(ip)), 
            ntohs(cliaddr.sin_port));

    while(1)
    {
        char buf[1024];
        memset(buf, 0, sizeof(buf));
        int len = read(cfd, buf, sizeof(buf));

        if(len > 0) {
            for(int i = 0; i < len; i++) {
                buf[i] = toupper(buf[i]);
            }
            write(cfd, buf, len);
        }
        else if(len == 0) {
            printf("client closed...");
            // close(cfd);
            break;
        }
        else {
            perror("read");
            exit(0);
        }
    }

    close(cfd);
    close(lfd);

    return 0;
}