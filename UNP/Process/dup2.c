
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    int fd;
    fd = open("ps.out", O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if(fd < 0) {
        perror("open ps.out error!");
        exit(1);
    }
    dup2(fd, STDOUT_FILENO);

    execlp("ps", "ps", "ax", NULL);
    
    //只有当execlp调用失败时才会执行下面的语句
    perror("exec error");
    exit(1);

    return 0;
}