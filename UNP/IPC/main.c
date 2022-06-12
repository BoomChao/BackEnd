

// #include <stdio.h>
// #include <unistd.h>
// #include <string.h>

// int main() {
//     const char *msg = "hello\n";

//     // printf("%lu\n", strlen(msg));

//     write(1, msg, strlen(msg));
//     char buf[1024];
//     // read(0, buf, strlen(msg));

//     return 0;
// }


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>

int var = 10;

int main()
{
    int *p;
    pid_t pid;

    p = mmap(NULL, 4, PROT_READ | PROT_WRITE , MAP_SHARED | MAP_ANON, -1, 0);

    if(p == MAP_FAILED) {
        perror("mmap failed:");
        exit(1);
    }

    if((pid = fork()) == 0) 
    {
        sleep(1);
        printf("In child, *p = %d, var = %d\n", *p, var);
    }
    else if(pid > 0)
    {
        *p = 2000;
        var = 1000;

        printf("In child, *p = %d, var = %d\n", *p, var);
        wait(NULL);
        // waitpid(-1, NULL, WUNTRACED);

        if(munmap(p, 4) < 0) { 
            perror("mumap error!");
            exit(1);
        }
    }
 
    return 0;
}

