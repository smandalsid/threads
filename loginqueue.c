#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t semaphore;

void *routine(void *arg)
{
    printf("Thread %d waiting in login queue\n", *(int *)arg);
    sem_wait(&semaphore);
    printf("Thread %d has logged in\n", *(int *)arg);
    sleep(1);
    printf("Hello from thread %d\n", *(int *)arg);
    printf("Thread %d logged out\n", *(int *)arg);
    sem_post(&semaphore);
    free(arg);
}

int main()
{
    pthread_t t[4];
    int i;
    sem_init(&semaphore, 0, 1);
    int *a;
    for(i=0;i<4;i++)
    {
        a=malloc(sizeof(int));
        *a=i;
        if(pthread_create(&t[i], NULL, &routine, a)!=0)
        {
            perror("Thread was not created\n");
        }
    }
    for(i=0;i<4;i++)
    {
        if(pthread_join(t[i], NULL)!=0)
        {
            perror("Thread was not joined\n");
        }
    }

    sem_destroy(&semaphore);

    return 0;
}