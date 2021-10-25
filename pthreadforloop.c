#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

int mails=0;
pthread_mutex_t mutex;

void *routine()
{
    for (int i = 0; i < 1000000; i++)
    {
        pthread_mutex_lock(&mutex);
        mails+=1;
        pthread_mutex_unlock(&mutex);
    }
    
}

int main()
{
    pthread_mutex_init(&mutex,NULL);
    pthread_t t[8];
    int i;
    for (i=0;i<8;i++)
    {
        pthread_create(&t[i],NULL,routine,NULL);
        printf("Thread %d started\n",i);
    }
    for (i=0;i<8;i++)
    {
        pthread_join(t[i],NULL);
        printf("Thread %d ended\n",i);
    }
    printf("Mails: %d\n",mails);
    return 0;
}