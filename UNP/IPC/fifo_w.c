#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd, i;
    char buf[4096];

    if(argc < 2) {
        return -1;
    }

    fd = open(argv[1], O_WRONLY);

    i = 0;
    while(1)
    {
        sprintf(buf, "hello world %d\n", i++);

        write(fd, buf, strlen(buf));
        sleep(1);
    }

    close(fd);

    return 0;
}

