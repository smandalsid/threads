// #include<stdio.h>
#include<pthread.h>
// #include<stdlib.h>
#include<iostream>
using namespace std;

void *routine(void *ptr)
{
    cout<<"This is a thread from cpp code\n";
    return NULL;
}

int main()
{
    pthread_t t1;
    pthread_t t2;

    if(pthread_create(&t1, NULL, routine, NULL)!=0)
    {
        return 1;
    }
    if(pthread_create(&t2, NULL, routine, NULL)!=0)
    {
        return 2;
    }
    if(pthread_join(t2, NULL)!=0)
    {
        return 3;
    }
    if(pthread_join(t1, NULL)!=0)
    {
        return 4;
    }
    
    return 0;
}