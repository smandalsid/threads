#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

int mails=0;
pthread_mutex_t mutex;

void *routine()
{
    for (int i=0;i<1000000;i++)
    {
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
    }
}

int main()
{
    pthread_t t1,t2, t3, t4;
    pthread_mutex_init(&mutex,NULL);
    pthread_create(&t1, NULL, routine, NULL);
    pthread_create(&t2, NULL, routine, NULL);
    pthread_create(&t3, NULL, routine, NULL);
    pthread_create(&t4, NULL, routine, NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    pthread_join(t4,NULL);
    pthread_mutex_destroy(&mutex);
    printf("Mails: %d\n", mails);
    return 0;
}