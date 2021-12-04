#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

int count=0;

void *routine()
{
    for(int i=0;i<10000;i++)
    {
        count++;
    }
}

int main()
{
    pthread_t t1, t2;    
    pthread_create(&t1, NULL, &routine, NULL);
    pthread_create(&t2, NULL, &routine, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // one solution to remove the race condition here is to put pthread_join(t1, NULL) beforecreating the second thread

    printf("%d\n", count);
    return 0;
}