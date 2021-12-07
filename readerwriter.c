#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

int readers=0;
pthread_mutex_t mutex;
sem_t wrt;

int data=1;

void *reader(void *arg)
{
    pthread_mutex_lock(&mutex);
    readers++;
    if(readers==1)
    {
        sem_wait(&wrt);
    }
    pthread_mutex_unlock(&mutex);

    printf("Reader %d reading the data, data-%d\n", *(int *)arg,  data);
    free(arg);

    pthread_mutex_lock(&mutex);
    readers--;
    if(readers==0)
    {
        sem_post(&wrt);
    }
    pthread_mutex_unlock(&mutex);
}

void *writer(void *arg)
{
    sem_wait(&wrt);
    data=rand();
    printf("Writer %d writing data\n", *(int *)arg);
    printf("New data written, data-%d\n", data);
    free(arg);
    sem_post(&wrt);
}

int main()
{
    pthread_t r1, r2, w1, w2;
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt, 0, 1);

    int *a;

    a=malloc(sizeof(int));
    *a=1;
    
    if(pthread_create(&r1, NULL, &reader, a)!=0)
    {
        perror("Failed to create thread\n");
    }

    *a=1;
    if(pthread_create(&w1, NULL, &writer, a)!=0)
    {
        perror("Failed to create thread\n");
    }

    *a=2;
    if(pthread_create(&r2, NULL, &reader, a)!=0)
    {
        perror("Failed to create thread\n");
    }

    *a=2;
    if(pthread_create(&w2, NULL, &writer, a)!=0)
    {
        perror("Failed to create thread\n");
    }

    if(pthread_join(r1, NULL)!=0)
    {
        perror("Failed to join thread\n");
    }
    if(pthread_join(w1, NULL)!=0)
    {
        perror("Failed to join thread\n");
    }
    if(pthread_join(r2, NULL)!=0)
    {
        perror("Failed to join thread\n");
    }
    if(pthread_join(w2, NULL)!=0)
    {
        perror("Failed to join thread\n");
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);
    return 0;
}