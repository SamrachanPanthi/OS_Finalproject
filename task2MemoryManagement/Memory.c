#include <stdio.h>

#define FRAME_COUNT 3
#define PAGE_SIZE 4
#define TOTAL_REQUESTS 13

int gameRequests[TOTAL_REQUESTS] =
{
    7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2
};
const char *gameAssests[] =
{
    "Map Data",          // 0
    "Player Texture",    // 1
    "Weapon Model",      // 2
    "Inventory Data",    // 3
    "Sound Effects",     // 4
    "Physics Engine",    // 5
    "NPC Data",          // 6
    "Quest Data"         // 7
};
void displayFrames(int frames[])
{
    for (int i = 0; i < FRAME_COUNT; i++)
    {
        if (frames[i] == -1)
        {
            printf("- ");
        }
        else
        {
            printf("%d ", frames[i]);
        }
    }
}
void simulateFIFO()
{
    int frames[FRAME_COUNT];

    int hits = 0;
    int faults = 0;

    int pointer = 0;

    for (int i = 0; i < FRAME_COUNT; i++)
    {
        frames[i] = -1;
    }

    printf("\n Algorithm  FIFO \n");

    for (int i = 0; i < TOTAL_REQUESTS; i++)
    {
        int found = 0;

        for (int j = 0; j < FRAME_COUNT; j++)
        {
            if (frames[j] == gameRequests[i])
            {
                found = 1;
                hits++;
                break;
            }
        }

        if (!found)
        {
            faults++;

            frames[pointer] = gameRequests[i];

            pointer = (pointer + 1) % FRAME_COUNT;
        }

        printf("Loading  %s -> ",gameAssests[ gameRequests[i]]);

        displayFrames(frames);

        if (found)
        {
            printf(" Hit\n");
        }
        else
        {
            printf(" Fault\n");
        }
    }
    printf("\nTotal Hits      : %d\n", hits);

printf("Total Faults    : %d\n", faults);

printf("Hit Ratio       : %.2f\n",
       (float) hits / TOTAL_REQUESTS);

printf("Miss Ratio      : %.2f\n",
       (float) faults / TOTAL_REQUESTS);
}
void simulateLRU()
{
    int frames[FRAME_COUNT];
    int recent[FRAME_COUNT];

    int hits = 0;
    int faults = 0;

    for (int i = 0; i < FRAME_COUNT; i++)
    {
        frames[i] = -1;
        recent[i] = -1;
    }

    printf("\n LRU \n");

    for (int i = 0; i < TOTAL_REQUESTS; i++)
    {
        int found = -1;

        for (int j = 0; j < FRAME_COUNT; j++)
        {
            if (frames[j] == gameRequests[i])
            {
                found = j;
                break;
            }
        }

        if (found != -1)
        {
            hits++;
            recent[found] = i;
        }
        else
        {
            faults++;

            int empty = -1;

            for (int j = 0; j < FRAME_COUNT; j++)
            {
                if (frames[j] == -1)
                {
                    empty = j;
                    break;
                }
            }

            if (empty != -1)
            {
                frames[empty] = gameRequests[i];
                recent[empty] = i;
            }
            else
            {
                int lru = 0;

                for (int j = 1; j < FRAME_COUNT; j++)
                {
                    if (recent[j] < recent[lru])
                    {
                        lru = j;
                    }
                }

                frames[lru] = gameRequests[i];
                recent[lru] = i;
            }
        }

        printf("Loading  %s -> ", gameAssests[gameRequests[i]]);

        displayFrames(frames);

        if (found != -1)
        {
            printf(" Hit\n");
        }
        else
        {
            printf(" Fault\n");
        }
    }
    printf("\nTotal Hits      : %d\n", hits);

printf("Total Faults    : %d\n", faults);

printf("Hit Ratio       : %.2f\n",
       (float) hits / TOTAL_REQUESTS);

printf("Miss Ratio      : %.2f\n",
       (float) faults / TOTAL_REQUESTS);
}
int main()
{
    printf(" GAME ENGINE MEMORY SIMULATOR\n");
    printf("Page Size : %d KB\n", PAGE_SIZE);
    printf("Frames    : %d\n", FRAME_COUNT);
    simulateFIFO();
    simulateLRU();
    return 0;
}
