#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<time.h>


void *dice()
{
    int value;
    value=rand()%6+1;
    int *res = malloc(sizeof(int));
    *res=value;
    printf("Pointer from function: %p\n", res);
    return (void *)res;
}


int main()
{
    pthread_t t;
    srand(time(NULL));
    pthread_create(&t, NULL, &dice, NULL);
    
    int *res;
    pthread_join(t, (void **)&res);
    
    printf("Random number generated: %d\n", *res);
    printf("Pointer from main: %p\n", res);
    free(res);
    return 0;
}