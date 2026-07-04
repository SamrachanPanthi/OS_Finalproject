#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define THREADS 3

int *shared;
pthread_mutex_t lock;
sem_t sem;

// Worker thread
void* task(void* arg)
{
    int id = *(int*)arg;

    sem_wait(&sem);

    printf("Thread %d is running\n", id);

    sem_post(&sem);

    return NULL;
}

int main()
{
    pthread_t t[THREADS];
    int id[THREADS] = {1,2,3};

    shared = (int*)malloc(sizeof(int));

    if(shared == NULL)
    {
        printf("Memory allocation failed!\n");
        return 1;
    }

    *shared = 0;

    printf("Memory allocated successfully.\n");
    printf("Shared value = %d\n", *shared);

    sem_init(&sem,0,2);

    for(int i=0;i<THREADS;i++)
    {
        pthread_create(&t[i],NULL,task,&id[i]);
    }

    for(int i=0;i<THREADS;i++)
    {
        pthread_join(t[i],NULL);
    }

    sem_destroy(&sem);
    free(shared);

    return 0;
}
