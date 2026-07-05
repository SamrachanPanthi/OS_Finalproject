
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int *completedOrders;

void *orderThread(void *arg)
{
    printf("Order Thread Started.\n");
    return NULL;
}

void *kitchenThread(void *arg)
{
    printf("Kitchen Thread Started.\n");
    return NULL;
}

void *billingThread(void *arg)
{
    printf("Billing Thread Started.\n");
    return NULL;
}

int main()
{
    pthread_t t1,t2,t3;

    completedOrders=(int *)malloc(sizeof(int));

    if(completedOrders==NULL)
    {
        printf("Memory Allocation Failed!\n");
        return 1;
    }

    *completedOrders=0;

    printf("Restaurant Order Management System\n\n");

    pthread_create(&t1,NULL,orderThread,NULL);
    pthread_create(&t2,NULL,kitchenThread,NULL);
    pthread_create(&t3,NULL,billingThread,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);

    printf("\nCompleted Orders = %d\n",*completedOrders);

    free(completedOrders);

    return 0;
}

