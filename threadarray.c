#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

int count=0;
pthread_mutex_t mutex;

void *routine()
{
    pthread_mutex_lock(&mutex);
    for(int i=0;i<10000;i++)
    {
        count++;
    }
    pthread_mutex_unlock(&mutex);
}


int main()
{
    pthread_t t[10];
    int i;
    pthread_mutex_init(&mutex, NULL);
    for(i=0;i<10;i++)
    {
        pthread_create(&t[i], NULL, &routine, NULL);
        printf("Thread %d was created\n", i+1);
    }
    for(i=0;i<10;i++)
    {
        pthread_join(t[i], NULL);
        printf("Thread %d was joined\n", i+1);
    }

    pthread_mutex_destroy(&mutex);
    printf("%d\n", count);

    return 0;
}