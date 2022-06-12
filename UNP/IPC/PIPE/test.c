
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

/*
int main(void)
{
    int fd[2];
    pipe(fd);
    pid_t pid = fork();

    if(pid == 0) {
        close(fd[1]);
        char line[100];
        int n = read(fd[0], line, 100);
        printf("%d %s \n", n, line);
    }
    else {
        close(fd[0]);
        write(fd[1], "hello!", 6);
    }

    getchar();

    return 0;
}

*/


int main(char argc, char *argv[]) 
{
    int fd = open("test1.c", O_RDONLY);
    
    if(fd == -1) {
        perror("open test1.cc");
        exit(1);
    }
    else {
        printf("%d\n", fd);
    }

    return 0;
}