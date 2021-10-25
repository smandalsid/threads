#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *rolldie()
{
    int value = (rand() % 5) + 1;
    int *result=malloc(sizeof(int));
    *result=value;
    return (void *)result;
}

int main()
{
    pthread_t th[4];
    int *res;
    int i;
    for (i=0;i<4;i++)
    {
        pthread_create(&th[i],NULL,&rolldie,NULL);
    }

    for (i=0;i<4;i++)
    {
        pthread_join(th[i], (void**)&res);
        printf("Value from die %d: %d\n", i, *res);
        free(res);
    }

    return 0;
}