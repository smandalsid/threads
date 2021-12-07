#include<pthread.h>
#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
sem_t room;
sem_t chopsticks[4];
void eat(int phil) {
    printf("\nPhilosopher %d is eating",phil);
}
void * phil(void * num) {
    int phil=*(int *)num;
    sem_wait(&room);
    printf("\nPhilosopher %d has entered room",phil);
    sem_wait(&chopsticks[phil]);
    sem_wait(&chopsticks[(phil+1)%4]);
    eat(phil);
    sleep(2);
    printf("\nPhilosopher %d has finished eating",phil);
    sem_post(&chopsticks[(phil+1)%4]);
    sem_post(&chopsticks[phil]);
    sem_post(&room);
}
int main() {
    int i,array[4];
    pthread_t id[4];
    sem_init(&room,0,4);
    for(i=0;i<4;i++)
        sem_init(&chopsticks[i],0,1);  
    for(i=0;i<4;i++){
        array[i]=i;
        pthread_create(&id[i],NULL,phil,(void *)&array[i]);
    }
    for(i=0;i<4;i++)
        pthread_join(id[i],NULL);
}