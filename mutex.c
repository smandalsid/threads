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
    pthread_t t1, t2;
    pthread_mutex_init(&mutex, NULL);

    if(pthread_create(&t1, NULL, &routine, NULL)!=0)
    {
        return 1;
    }
    
    if(pthread_create(&t2, NULL, &routine, NULL)!=0)
    {
        return 2;
    }
    
    if(pthread_join(t1, NULL)!=0)
    {
        return 3;
    }
    
    if(pthread_join(t2, NULL)!=0)
    {
        return 4;
    }

    pthread_mutex_destroy(&mutex);
    printf("%d\n", count);
    return 0;
}