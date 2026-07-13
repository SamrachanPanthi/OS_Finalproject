#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define QUANTUM 2

pthread_mutex_t lock;
sem_t sem;

int *completedActions;
//deadlock prevention REsource


pthread_mutex_t resource1;
pthread_mutex_t resource2;
void *playerThread(void *arg)
{
    sem_wait(&sem);

    for(int i = 0; i < 3; i++)
    {
        pthread_mutex_lock(&lock);

        (*completedActions)++;
        printf("Player  Thread  processed action  %d\n", *completedActions);

        pthread_mutex_unlock(&lock);
        sleep(1);
    }

    sem_post(&sem);
    return NULL;
}

void *enemyAIThread(void *arg)
{
    sem_wait(&sem);

    for(int i = 0; i < 3; i++)
    {
        pthread_mutex_lock(&lock);

        (*completedActions)++;
        printf("Enemy AI Thread processed action  %d\n", *completedActions);

        pthread_mutex_unlock(&lock);
        sleep(1);
    }

    sem_post(&sem);
    return NULL;
}

void *scoreThread(void *arg)
{
    sem_wait(&sem);

    for(int i = 0; i < 3; i++)
    {
        pthread_mutex_lock(&lock);

        (*completedActions)++;
        printf("Score Thread updated score %d\n", *completedActions);

        pthread_mutex_unlock(&lock);
        sleep(1);
    }

    sem_post(&sem);
    return NULL;
}
void roundRobin()
{
    int burst[3]={5,3,4};

    char *process[3]={
        "PLayer",
        "Enemy AI",
        "Score System"
    };

    int completed=0;

    printf("\n Round Robin \n");

    while(completed<3)
    {
        for(int i=0;i<3;i++)
        {
            if(burst[i]>0)
            {
                if(burst[i]>QUANTUM)
                {
                    printf("%s executes for %d units\n",
                            process[i],QUANTUM);

                    burst[i]-=QUANTUM;
                }
                else
                {
                    printf("%s completed.\n",process[i]);

                    burst[i]=0;

                    completed++;
                }

                sleep(1);
            }
        }
    }

}
void *GameResource(void *arg)
{
    const char *name = (const char *)arg;

    pthread_mutex_lock(&resource1);
    printf("%s locked Resource 1\n", name);

    sleep(1);

    pthread_mutex_lock(&resource2);
    printf("%s locked Resource 2\n", name);

    printf("%s completed successfully\n", name);

    pthread_mutex_unlock(&resource2);
    pthread_mutex_unlock(&resource1);

    return NULL;
}
int main()
{
    pthread_t t1, t2, t3;
    pthread_t d1,d2;

    completedActions = (int *)malloc(sizeof(int));
    *completedActions = 0;

    pthread_mutex_init(&lock, NULL);
    sem_init(&sem, 0, 2);
    pthread_mutex_init(&resource1,NULL);
    pthread_mutex_init(&resource2,NULL);
    printf("Multiplayer video Game  Management System\n\n");

    pthread_create(&t1, NULL, playerThread, NULL);
    pthread_create(&t2, NULL, enemyAIThread, NULL);
    pthread_create(&t3, NULL, scoreThread, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    
    roundRobin();
    // Game REsource Syncronization Demo
    pthread_create(&d1, NULL, GameResource, "Manager");
    pthread_create(&d2, NULL, GameResource, "Supervisor");

    pthread_join(d1, NULL);
    pthread_join(d2, NULL);
    printf("\nCompleted Actions = %d\n", *completedActions);

    pthread_mutex_destroy(&lock);
    sem_destroy(&sem);
    pthread_mutex_destroy(&resource1);
    pthread_mutex_destroy(&resource2);
    printf("\nTotal game ACtions = %d\n",*completedActions);
    free(completedActions);

    return 0;
}
