#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<time.h>

void *dice()
{
    int *res;
    int value;
    value=rand()%6+1;
    res=malloc(sizeof(int));
    *res=value;
    return res;
}

int main()
{

    pthread_t t[2];
    int i;

    for(i=0;i<2;i++)
    {
        srand(time(NULL));
        pthread_create(&t[i], NULL, &dice, NULL);
        
    }

    int *res;
    for(i=0;i<2;i++)
    {
        pthread_join(t[i], (void **)&res);
        printf("Value of dice %d: %d\n", i, *res);
    }
    return 0;
}