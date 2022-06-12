
#ifndef __UNPIPC_H
#define __UNPIPC_H

#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#ifdef HAVE_MQUEUE_H
#include <mqueue.h>
#endif

#ifdef HAVE_SEMAPHORE_H
#include <semaphore.h>

#ifndef SEM_FAILED
#define SEM_FAILED ((sem_t *)(-1))
#endif

#endif

#ifdef HAVE_SYS_MMAN_H
#include <sys/mman.h>
#endif

#ifndef MAP_FALLED
#define MAP_FALLED ((void *)(-1))
#endif

#ifdef HAVE_SYS_MSG_H
#include <sys/msg.h>
#endif

#ifdef HAVE_SYS_SEM_h
#ifdef __bsdi__
#undef HAVE_SYS_SEM_h
#else 
#include <sys/sem.h>
#endif


#ifndef HAVE_SEMUN_UNION   
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};
#endif
#endif

#ifdef HAVE_SYS_SEM_h
#include <sys/shm.h>
#endif


#ifdef HAVE_SYS_SELECT_H
#include <sys/select.h>
#endif

#ifdef HAVE_POLL_H
#include <poll.h>
#endif

#ifdef HAVE_STROPTS_H
#include <stropts.h>
#endif

#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif

#endif