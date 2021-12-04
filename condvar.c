#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

int fuel=0;
pthread_mutex_t mutexfuel;
pthread_cond_t fuelcond;

void *pump(void *arg)
{
    for(int i=0;i<5;i++)
    {
        pthread_mutex_lock(&mutexfuel);
        fuel+=15;
        printf("Fueling car... fuel: %d\n", fuel);
        pthread_cond_signal(&fuelcond);
        pthread_mutex_unlock(&mutexfuel);
        sleep(1);
    }
}

void *car(void *arg)
{
    pthread_mutex_lock(&mutexfuel);
    while(fuel<20)
    {
        printf("Fuel not enough\n");
        pthread_cond_wait(&fuelcond, &mutexfuel);
    }
    fuel-=20;
    printf("Car consuming fuel.. fuel: %d\n", fuel);
    pthread_mutex_unlock(&mutexfuel);
    sleep(1);
}

int main()
{
    pthread_t t[2];
    pthread_mutex_init(&mutexfuel, NULL);
    pthread_cond_init(&fuelcond, NULL);
    for(int i=0;i<2;i++)
    {
        if(i==1)
        {
            pthread_create(&t[i], NULL, &pump, NULL);
        }
        else
        {
            pthread_create(&t[i], NULL, &car, NULL);
        }
    }
    for(int i=0;i<2;i++)
    {
        pthread_join(t[i], NULL);
    }
    pthread_mutex_destroy(&mutexfuel);
    pthread_cond_destroy(&fuelcond);
    return 0;
}