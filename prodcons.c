// PROBLEM STATEMENT

// 

#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<stdio.h>

#define maxlim 5
#define buffercap 5

sem_t empty;
sem_t full;

int in=0;
int out=0;

int buffer[buffercap];

pthread_mutex_t mutex;

void *producer(void *producerno)
{
    int item;
    for (int i=0;i<maxlim;i++)
    {
        item=rand();
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in]=item;
        printf("producer %d: insert item %d at %d\n", *((int *)producerno),buffer[in], in);
        in=(in+1)%buffercap;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *consumerno)
{
    for (int i=0;i<maxlim;i++)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int item=buffer[out];
        printf("Consumer %d: Remove item %d from %d\n", *((int *)consumerno), item, out);
        out=(out+1)%buffercap;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        
    }
}

int main()
{
    pthread_t producer[5], consumer[5];
    pthread_mutex_init(&mutex, NULL);
    
    sem_init(&empty,0,buffercap);
    sem_init(&full,0,0);
    
    int a[5]={1,2,3,4,5};
    int i;
    
    for (i=0;i<5;i++)
    {
        pthread_create(&producer[i],NULL,(void *)producer,(void *)&a[i]);
    }
    
    for (i=0;i<5;i++)
    {
        pthread_create(&consumer[i],NULL,(void *)consumer, (void *)&a[i]);
    }
    
    // pthread_create(&producer,NULL,(void *)producer,(void *)&a[0]);
    // pthread_create(&consumer,NULL,(void *)consumer, (void *)&a[0]);
    
    // pthread_join(producer,NULL);
    // pthread_join(consumer,NULL);
    
    for (i=0;i<5;i++)
    {
        pthread_join(producer[i],NULL);   
    }
    
    for (i=0;i<5;i++)
    {
        pthread_join(consumer[i],NULL);   
    }
    
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
}

// #include<pthread.h>
// #include<semaphore.h>
// #include<stdio.h>
// #include<stdlib.h>
// #include<unistd.h>

// #define buffcap 5
// #define empty 0
// #define full 0

// char buffer[buffcap];
// int nextin=0;
// int nextout=0;

// sem_t empty_sem_mutex;
// sem_t full_sem_mutex;

// void put(char item)
// {
//     int value;
//     sem_wait(&empty_sem_mutex);
//     buffer[nextin]=item;
//     nextin=(nextin+1)%buffcap;
//     printf("Producing %c nextin %d ascii=%d\n", item, nextin, item);
//     if (nextin==full)
//     {
//         sem_post(&full_sem_mutex);
//         sleep(1);
//     }
//     sem_post(&empty_sem_mutex);
// }

// void * producer()
// {
//     int i;
//     for (i=0; i<10; i++)
//     {
//         put((char)'A'+i%26);
//     }
// }

// void get()
// {
//     int item;
//     sem_wait(&full_sem_mutex);
//     item=buffer[nextout];
//     nextout=(nextout+1)%buffcap;
//     printf("\t..consuming %c ...nextout %d ASCII=%d\n", item, nextout, item);
//     if (nextout==empty)
//     {
//         sleep(1);
//     }
//     sem_post(&full_sem_mutex);
    
// }

// void *consumer()
// {
//     int i;
//     for(i=0;i<10;i++)
//     {
//         get();
//     }
// }

// int main()
// {
//     pthread_t ptid, ctid;
    
//     sem_init(&empty_sem_mutex,0,1);
//     sem_init(&full_sem_mutex,0,0);
    
//     if (pthread_create(&ptid, NULL, producer, NULL))
//     {
//         printf("\nERROR creating thread 1");
//         exit(1);
//     }
    
//     if (pthread_create(&ctid, NULL, consumer, NULL))
//     {
//         printf("\n ERROR creatin thread 2");
//     }
    
//     if (pthread_join(ptid, NULL))
//     {
//         printf("\n Error joining thread");
//         exit(1);
        
//     }
    
//     if (pthread_join(ctid, NULL))
//     {
//         printf("\n ERROR joining thread");
//         exit(1);
//     }
    
//     sem_destroy(&empty_sem_mutex);
//     sem_destroy(&full_sem_mutex);
    
//     pthread_exit(NULL);
//     return 1;
// }