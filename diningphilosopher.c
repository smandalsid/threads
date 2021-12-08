#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t chopsticks[5];

void *philosopher(void *arg)
{
    int a=*(int *)arg;
    printf("Philosopher %d is hungry\n", a);
    printf("Philosopher %d tries picking up left chopstrick\n", a);
    sem_wait(&chopsticks[a]);
    printf("Philosopher %d picked up left chopstick\n", a);
    printf("Philosopher %d tries to pick up right chopstick\n", a);
    sem_wait(&chopsticks[(a+1)%5]);
    printf("Philosopher %d picks up right chopstick\n", a);
    printf("Philosopher %d starts eating\n", a);
    sleep(2);
    printf("Philosopher %d finished eating\n", a);
    sem_post(&chopsticks[a]);
    printf("Philosopher %d drops left chopstick\n", a);
    sem_post(&chopsticks[(a+1)%5]);
    printf("Philosopher %d drops right chopstick\n", a);
    free(arg);
}

int main()
{
    pthread_t t[5];
    int i;

    for(i=0;i<5;i++)
    {
        sem_init(&chopsticks[i], 0, 1);
    }

    int *a;

    for(i=0;i<5;i++)
    {
        a=malloc(sizeof(int));
        *a=i;
        if(pthread_create(&t[i], NULL, &philosopher, a)!=0)
        {
            perror("Failed to create thread\n");
        }
    }

    for(i=0;i<5;i++)
    {
        if(pthread_join(t[i], NULL)!=0)
        {
            perror("Failed to join thread\n");
        }
    }

    for(i=0;i<5;i++)
    {
        sem_destroy(&chopsticks[i]);
    }

    return 0;
}