#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int ar[]={1,2,3,4,5,6,7,8,9,10};

void *routine(void *arg)
{
    int index = *(int *)arg;
    int tot=0;
    for(int i=index;i<index+5;i++)
    {
        tot+=ar[i];
    }
    *(int *)arg=tot;
    return arg;
}

int main()
{
    pthread_t t[2];
    int i;
    int *index;
    for(i=0;i<2;i++)
    {
        index=malloc(sizeof(int));
        if(i==0)
        *index=0;
        else
        *index=5;
        pthread_create(&t[i], NULL, &routine, index);
    }
    int totans=0;
    for(i=0;i<2;i++)
    {
        int *ans;
        pthread_join(t[i], (void **)&ans);
        printf("Sum of half %d of array: %d\n", i+1, *(int *)ans);
        totans+=*ans;
        free(ans);
    }
    printf("Total sum: %d\n", totans);
    return 0;
}