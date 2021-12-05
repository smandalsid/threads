#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

int buffer[10];
int count=-1;

pthread_mutex_t mutex;

sem_t empty;
sem_t full;

void *producer(void *args)
{
    while(1)
    {
        // sleep(1);
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        int x= rand()%100;
        buffer[++count]=x;
        printf("Produced: %d\n", x);
        // if(count<10)t>-1)
        // {
        //     printf("Obtained from the buffer: %d\n",buffer[count--]);
        // }
        // else
        // {
        //     printf("LOLOLOL\n");
        // }
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *args)
{
    while(1)
    {
        sleep(1);
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        printf("Consumed: %d\n", buffer[count]);
        count--;
        // if(count>-1)
        // {
        //     printf("Obtained from the buffer: %d\n",buffer[count--]);
        // }
        // else
        // {
        //     printf("LOLOLOL\n");
        // }
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}  

int main()
{
    pthread_t t[2];
    int i;
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, 10);
    sem_init(&full, 0, 0);
    for(i=0;i<2;i++)
    {
        if(i%2==0)
        {
            if(pthread_create(&t[i], NULL, &producer, NULL)!=0)
            {
                perror("Failed to create thread\n");
            }
        }
        else
        {
            if(pthread_create(&t[i], NULL, &consumer, NULL)!=0)
            {
                perror("Failed to create thread\n");
            }
        }
    }
    for(i=0;i<2;i++)
    {
        if(pthread_join(t[i], NULL)!=0)
        {
            perror("Failed to join thread\n");
        }
    }
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
}