#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

void *rolldie()
{
    int value=(rand() % 5 )+1;
    int *result = malloc(sizeof(int));
    *result=value;
    return (void*) result;
}

int main()
{
    pthread_t t;
    int *res;
    pthread_create(&t, NULL, &rolldie, NULL);
    pthread_join(t,(void **)&res);
    printf("Result: %d\n", *res);
    free(res);
    return 0;
}