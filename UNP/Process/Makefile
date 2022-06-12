obj = demo.c
target = demo
CC = gcc
$(target):$(obj)
	$(CC) $(obj) -o $(target) -lpthread

signal : signal.c
	gcc signal.c -o signal

server : server.c
	gcc server.c -o server -Wall -g

pthread_mutex : pthread_mutex.c
	gcc pthread_mutex.c -o pthread_mutex -lpthread

pthread_rwlock : pthread_rwlock.c
	gcc pthread_rwlock.c -o pthread_rwlock -lpthread

pthread_cond : pthread_cond.c
	gcc pthread_cond.c -o pthread_cond -lpthread

semaphore : semaphore.c
	gcc semaphore.c -o semaphore -lpthread

process_mutex : process_mutex.c
	gcc process_mutex.c -o process_mutex -lpthread

fcntl : fcntl.c
	gcc fcntl.c -o fcntl -lpthread

client : client.c
	gcc client.c -o client

demo.o:demo.c
	gcc -c demo.c -o demo -lpthread
