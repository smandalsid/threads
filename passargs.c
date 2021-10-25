#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

int primes[10]={2,3,5,7,11,13,17,19,23,29};

void  *routine(void *arg)
{
    int index= *(int *)arg;
    printf("%d\n", primes[index]);
    // printf("%d\n", *(primes+index));
    // or printf("%d\n", *(primes+i);)
    free(arg);
}

int main()
{
    pthread_t th[10];
    int i;
    int *a;
    for (i=0;i<10;i++)
    {
        a=malloc(sizeof(int));
        *a=i;
        pthread_create(&th[i], NULL, &routine, a);
    }
    for (i=0;i<10;i++)
    {
        pthread_join(th[i], NULL);  
    }
    return 0;
}