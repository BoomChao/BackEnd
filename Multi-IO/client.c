#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main()
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd == -1) {
        perror("socket");
        exit(0);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9999);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);
    int res = connect(fd, (struct sockaddr*)&addr, sizeof(addr));
    if(res == -1) {
        perror("connect");
        exit(0);
    }

    while(1)
    {
        char recvBuf[1024];

        fgets(recvBuf, sizeof(recvBuf), stdin);

        write(fd, recvBuf, strlen(recvBuf) + 1);

        read(fd, recvBuf, sizeof(recvBuf));
        
        printf("%s", recvBuf);
    }

    close(fd);

    return 0;
}