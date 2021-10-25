// #include<stdio.h>
// #include<pthread.h>
// #include<unistd.h>

// void *routine()
// {
//     printf("Test from threads\n");
//     sleep(1);
//     printf("Ending thread\n");
// }

// int main(int argc, char *argv[])
// {
//     pthread_t t1, t2;
//     pthread_create(&t1, NULL, &routine, NULL);
//     pthread_create(&t2, NULL, &routine, NULL);
//     pthread_join(t1, NULL);
//     pthread_join(t2, NULL);
//     return 0;
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include <unistd.h>

// void *routine()
// {
//     printf("Process id: %d\n", getpid());
// }

// int main(int argc, char *argv[])
// {
//     pthread_t t1;
//     if (pthread_create(&t1, NULL, &routine, NULL))
//     {
//         printf("1");
//     }
//     if (pthread_join(t1,NULL)==0)
//     {
//         printf("threadjoin was successful");
//     }
//     return 0;
// }

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>

int x=1;

void *routine()
{
    x++;
    sleep(2);
    printf("%d\n",x);
}

void *routine2()
{
    sleep(2);
    printf("%d\n",x);
}

int main(int argc, char *argv[])
{
    pthread_t t1,t2;
    pthread_create(&t1,NULL,routine,NULL);
    pthread_create(&t2,NULL,routine2,NULL);
    pthread_join(t1,NULL);
    // pthread_join(t2,NULL);
    return 0;
}