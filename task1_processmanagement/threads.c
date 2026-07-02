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
    printf("Process Management Assignment\n");
    return 0;
}
