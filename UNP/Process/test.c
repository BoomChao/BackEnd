//循环创建子进程

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    pid_t pid;
    printf("XXXXXXX\n");

    int i;
    for(i = 0; i < 5; i++) {
        pid = fork();
        if(pid == 0) {
            break;
        }
    }

    if(i < 5) {
        sleep(i);
        printf("I'm %d child, pid = %u\n", i+1, getpid());
    } else {
        sleep(i);
        printf("I'm parent\n");
    }

    return 0;
}
