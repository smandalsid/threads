#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

int buffer[10];
int pos;
int size=-1;

pthread_mutex_t mutex;

sem_t empty;
sem_t full;

void *producer(void *arg)
{
	sem_wait(&empty);
	pthread_mutex_lock(&mutex);
	int x=rand()%100+1;
	buffer[++size]=x;
	printf("Produced: %d\n", x);
	printf("The buffer:\n");
	for(int i=0;i<10;i++)
	{
		printf("%d ", buffer[i]);
	}
	printf("\n");
	pthread_mutex_unlock(&mutex);
	sem_post(&full);
}

void *consumer(void *arg)
{
	sem_wait(&full);
	pthread_mutex_lock(&mutex);
	int temp=buffer[0];
	for(int i=0;i<size;i++)
	{
		buffer[i]=buffer[i+1];
	}
	printf("Item consumed from buffer: %d\n", temp);
	size--;
	printf("The buffer:\n");
	for(int i=0;i<10;i++)
	{
		printf("%d ", buffer[i]);
	}
	printf("\n");
	pthread_mutex_unlock(&mutex);
	sem_post(&empty);
}

int main()
{
	pthread_mutex_init(&mutex, NULL);
	sem_init(&empty, 0, 10);
	sem_init(&full, 0, 0);

	pthread_t c, p[5];
	int i;

	if(pthread_create(&c, NULL, &consumer, NULL)!=0)
	{
		perror("Failed to create thread\n");
	}

	int *a;
	for(i=0;i<5;i++)
	{
		a=malloc(sizeof(a));
		*a=i;
		if(pthread_create(&p[i], NULL, &producer, a)!=0)
		{
			perror("Failed to create thread\n");
		}
	}

	if(pthread_join(c, NULL)!=0)
	{
		perror("Failed to join thread\n");
	}

	for(i=0;i<5;i++)
	{
		if(pthread_join(p[i], NULL)!=0)
		{
			perror("Failed to join thread\n");
		}
	}

	pthread_mutex_destroy(&mutex);
	sem_destroy(&empty);
	sem_destroy(&full);
	return 0;
}