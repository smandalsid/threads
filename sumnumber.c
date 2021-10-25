#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

int ar[10]={0,1,2,3,4,5,6,7,8,9};

void *routine(void *arg)
{
    int index=*(int *)arg;
    int tot=0;
    for (int i=index;i<index+5;i++)
    {
        tot+=ar[i];
    }
    printf("Local sum: %d\n", tot);
    *(int *)arg=tot;
    return arg;
}

int main()
{
    pthread_t th[2];
    int i;
    for (i=0;i<2;i++)
    {
        int *a;
        a=malloc(sizeof(int));
        if (i==0)
        {
            *a=0;
        }
        else
        {
            *a=5;
        }

        pthread_create(&th[i], NULL, &routine, a);
    }
    int sum=0;
    for (i=0;i<2;i++)
    {
        int *res;
        pthread_join(th[i], (void**)&res);
        sum+=*res;
        free(res);
    }
    printf("Total sum: %d\n", sum);
    return 0;
}