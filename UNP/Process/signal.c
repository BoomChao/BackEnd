
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>


int main() {
    int i;
    alarm(1);

    for(i = 0; ; i++) {
        printf("%d\n", i);
    }

    return 0;
}


/*
int main() {
    int i;
    pid_t pid, q;

    // abort();
    // raise(SIGSEGV);

    for(i = 0; i < 5; i++) {
        pid = fork();
        if(pid == -1) {
            exit(1);
        }
        else if(pid == 0) {    
            break;
        }
        else if(i == 2) {
            q = pid;
        } 
    }

    if(i < 5) {
        while(1) {
            printf("I'm child %d, getpid = %u\n", i, getpid());
            sleep(1);
        }
    }
    else {
        sleep(1);
        kill(q, SIGKILL);
        while(1);    
    }


    return 0;
}
*/
