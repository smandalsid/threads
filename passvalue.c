#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

int primes[]={2,3,5,7,11,13,17,19,23,29};

void *routine(void *arg)
{
    int index = *(int *)arg;
    printf("%d ", index);
    // free(arg);
}

int main()
{
    pthread_t t[10];
    int i;
    // int *index;
    for(i=0;i<10;i++)
    {
        // index=malloc(sizeof(int));
        // *index=i;
        if(pthread_create(&t[i], NULL, &routine, primes+i)!=0)
        {
            perror("Thread was not created\n");
        }
    }
    for(int i=0;i<10;i++)
    {
        if(pthread_join(t[i], NULL)!=0)
        {
            perror("Thread was not destroyed\n");
        }
    }
    return 0;
}