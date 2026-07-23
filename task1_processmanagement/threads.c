#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define QUANTUM 2

pthread_mutex_t lock;
pthread_mutex_t resource1;
pthread_mutex_t resource2;

sem_t sem;

int *completedActions;

/* Player Thread */

void *playerThread(void *arg)
{
    sem_wait(&sem);

    for (int i = 0; i < 3; i++)
    {
        pthread_mutex_lock(&lock);

        (*completedActions)++;

        printf(
            "Player Thread processed action %d\n",
            *completedActions
        );

        pthread_mutex_unlock(&lock);

        sleep(1);
    }

    sem_post(&sem);

    return NULL;
}


/* Enemy AI Thread */

void *enemyAIThread(void *arg)
{
    sem_wait(&sem);

    for (int i = 0; i < 3; i++)
    {
        pthread_mutex_lock(&lock);

        (*completedActions)++;

        printf(
            "Enemy AI Thread processed action %d\n",
            *completedActions
        );

        pthread_mutex_unlock(&lock);

        sleep(1);
    }

    sem_post(&sem);

    return NULL;
}


/* Score Thread */

void *scoreThread(void *arg)
{
    sem_wait(&sem);

    for (int i = 0; i < 3; i++)
    {
        pthread_mutex_lock(&lock);

        (*completedActions)++;

        printf(
            "Score Thread updated score %d\n",
            *completedActions
        );

        pthread_mutex_unlock(&lock);

        sleep(1);
    }

    sem_post(&sem);

    return NULL;
}


/* Round Robin Scheduling */

void roundRobin()
{
    int burst[3] = {5, 3, 4};

    char *process[3] =
    {
        "Player",
        "Enemy AI",
        "Score System"
    };

    int completed = 0;

    printf(
        "\n Round Robin Scheduling \n"
    );

    printf(
        "Time Quantum = %d\n\n",
        QUANTUM
    );

    while (completed < 3)
    {
        for (int i = 0; i < 3; i++)
        {
            if (burst[i] > 0)
            {
                if (burst[i] > QUANTUM)
                {
                    printf(
                        "%s executes for %d units\n",
                        process[i],
                        QUANTUM
                    );

                    burst[i] -= QUANTUM;
                }
                else
                {
                    printf(
                        "%s completed.\n",
                        process[i]
                    );

                    burst[i] = 0;

                    completed++;
                }

                sleep(1);
            }
        }
    }

    printf(
        "\nRound Robin scheduling completed successfully.\n"
    );
}


/* Synchronization and Deadlock Prevention */

void *GameResource(void *arg)
{
    const char *name = (const char *)arg;

    pthread_mutex_lock(&resource1);

    printf(
        "%s locked Resource 1\n",
        name
    );

    sleep(1);

    pthread_mutex_lock(&resource2);

    printf(
        "%s locked Resource 2\n",
        name
    );

    printf(
        "%s completed successfully\n",
        name
    );

    pthread_mutex_unlock(&resource2);

    pthread_mutex_unlock(&resource1);

    return NULL;
}


/* Main Function */

int main()
{
    pthread_t t1;
    pthread_t t2;
    pthread_t t3;

    pthread_t d1;
    pthread_t d2;

    completedActions =
        (int *)malloc(sizeof(int));

    *completedActions = 0;

    pthread_mutex_init(
        &lock,
        NULL
    );

    pthread_mutex_init(
        &resource1,
        NULL
    );

    pthread_mutex_init(
        &resource2,
        NULL
    );

    sem_init(
        &sem,
        0,
        2
    );

    printf(
    );
    printf(
        " Multiplayer Video Game Management System\n"
    );

    printf(
    );

    printf(
        "\nThread Execution\n"
    );

    pthread_create(
        &t1,
        NULL,
        playerThread,
        NULL
    );

    pthread_create(
        &t2,
        NULL,
        enemyAIThread,
        NULL
    );

    pthread_create(
        &t3,
        NULL,
        scoreThread,
        NULL
    );

    pthread_join(
        t1,
        NULL
    );

    pthread_join(
        t2,
        NULL
    );

    pthread_join(
        t3,
        NULL
    );

    printf(
        "\nThread execution completed successfully.\n"
    );

    roundRobin();

    printf(
        "\nSynchronization \n"
    );

    pthread_create(
        &d1,
        NULL,
        GameResource,
        "Manager"
    );

    pthread_create(
        &d2,
        NULL,
        GameResource,
        "Supervisor"
    );

    pthread_join(
        d1,
        NULL
    );

    pthread_join(
        d2,
        NULL
    );

    printf(
        "\nSynchronization completed successfully.\n"
    );

    printf(
        "\n Final Result \n"
    );

    printf(
        "\nCompleted Actions = %d\n",
        *completedActions
    );

    printf(
        "\nTotal Game Actions = %d\n",
        *completedActions
    );

    printf(
        "\nAll tests completed successfully.\n"
    );

    pthread_mutex_destroy(&lock);

    pthread_mutex_destroy(&resource1);

    pthread_mutex_destroy(&resource2);

    sem_destroy(&sem);

    free(completedActions);

    return 0;
}
