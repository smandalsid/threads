#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void *routine()
{
    printf("This is a thread from c code\n");
}

int main()
{
    pthread_t t1, t2;

    if(pthread_create(&t1, NULL, routine, NULL)!=0)
    {
        return 1;
    }
    
    if(pthread_create(&t2, NULL, routine, NULL)!=0)
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
    
    return 0;
}