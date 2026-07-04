#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>
#define THREADS 3
#define QUANTUM 2

int *shared;
pthread_mutex_t lock;
sem_t sem;
int main() {

    shared = (int*)malloc(sizeof(int));

    if (shared == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    *shared = 0;

    printf("Memory allocated successfully!\n");
    printf("Shared value = %d\n", *shared);

    free(shared);

    return 0;
}
