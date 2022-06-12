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
    int fd, len;
    char buf[4096];

    if(argc < 2) {
        return -1;
    }

    fd = open(argv[1], O_RDONLY);

    while(1)
    {
        len = read(fd, buf, sizeof(buf));
        write(STDOUT_FILENO, buf, len);
        // sleep(1);
    }

    close(fd);

    return 0;
}
