#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

pthread_mutex_t lock;
sem_t sem;

int *completedOrders;

void *orderThread(void *arg)
{
    sem_wait(&sem);

    for(int i = 0; i < 3; i++)
    {
        pthread_mutex_lock(&lock);

        (*completedOrders)++;
        printf("Order Thread processed order %d\n", *completedOrders);

        pthread_mutex_unlock(&lock);
        sleep(1);
    }

    sem_post(&sem);
    return NULL;
}

void *kitchenThread(void *arg)
{
    sem_wait(&sem);

    for(int i = 0; i < 3; i++)
    {
        pthread_mutex_lock(&lock);

        (*completedOrders)++;
        printf("Kitchen Thread prepared order %d\n", *completedOrders);

        pthread_mutex_unlock(&lock);
        sleep(1);
    }

    sem_post(&sem);
    return NULL;
}

void *billingThread(void *arg)
{
    sem_wait(&sem);

    for(int i = 0; i < 3; i++)
    {
        pthread_mutex_lock(&lock);

        (*completedOrders)++;
        printf("Billing Thread made bill %d\n", *completedOrders);

        pthread_mutex_unlock(&lock);
        sleep(1);
    }

    sem_post(&sem);
    return NULL;
}

int main()
{
    pthread_t t1, t2, t3;

    completedOrders = (int *)malloc(sizeof(int));
    *completedOrders = 0;

    pthread_mutex_init(&lock, NULL);
    sem_init(&sem, 0, 2);

    printf("Restaurant Order Management System\n\n");

    pthread_create(&t1, NULL, orderThread, NULL);
    pthread_create(&t2, NULL, kitchenThread, NULL);
    pthread_create(&t3, NULL, billingThread, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("\nCompleted Orders = %d\n", *completedOrders);

    pthread_mutex_destroy(&lock);
    sem_destroy(&sem);

    free(completedOrders);

    return 0;
}
