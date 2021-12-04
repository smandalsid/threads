#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

void *routine1()
{
    for (int i=0;i<5;i++)
    {
        printf("Routine 1: %d\n", i);
    }
}

void *routine2()
{
    for (int i=0;i<5;i++)
    {
        printf("Routine 2: %d\n", i);
    }
}

int main()
{
    pthread_t th1, th2;
    pthread_create(&th1, NULL, &routine1, NULL);
    pthread_create(&th2, NULL, &routine2, NULL);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    return 0;
}