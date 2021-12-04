#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>

#define THREAD_NUM 4

sem_t semaphore;

void *routine(void *arg)
{
    printf("Hello");
}

int main()
{
    pthread_t th[THREAD_NUM];
    sem_init(&semaphore, 0, 1); 
    // in the middle parameter we if we have one process having multiple threads we put 0 and if we have many process have multiple threads then we have 1.
    // the third parameter is the initial value of the semaphore
    int i;
    sem_destroy(&semaphore);
    return 0;
}