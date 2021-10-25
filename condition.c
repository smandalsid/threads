#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_mutex_t printmessage;
pthread_cond_t condprint;
int printqueue=0;

void *application(void *arg)
{
    int i;
    for (i=0;i<5;i++)
    {
        pthread_mutex_lock(&printmessage);
        printf("Producing message for printing from application(producer)\n");
        printqueue+=1;
        printf("Number of messages: %d\n", printqueue);
        pthread_mutex_unlock(&printmessage);
        pthread_cond_signal(&condprint);
        sleep(1);
    }
}

void *printer(void * arg)
{
    pthread_mutex_lock(&printmessage);
    while (printqueue<2)
    {
        printf("No printing jobs left\n");
        pthread_cond_wait(&condprint, &printmessage);
    }
    printf("Printer printing...(consumer)\n");
    printqueue-=2;
    printf("Number of printing jobs left: %d\n", printqueue);
    pthread_mutex_unlock(&printmessage);
    sleep(1);
}

int main()
{
    pthread_t th[2];
    pthread_mutex_init(&printmessage, NULL);
    pthread_cond_init(&condprint, NULL);
    for (int i=0;i<2;i++)
    {
        if (i==0)
        {
            pthread_create(&th[1], NULL, &printer, NULL);
        }
        else
        {
            pthread_create(&th[0], NULL, &application, NULL);
        }
    }
    for (int i=0;i<2;i++)
    {
        pthread_join(th[i], NULL);
    }
    pthread_mutex_destroy(&printmessage);
    pthread_cond_destroy(&condprint);
    return 0;
}