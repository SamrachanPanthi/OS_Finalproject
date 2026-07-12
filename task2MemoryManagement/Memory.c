#include <stdio.h>

#define FRAME_COUNT 3
#define PAGE_SIZE 4
#define TOTAL_REQUESTS 13

int videoPages[TOTAL_REQUESTS] =
{
    7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2
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

    printf("\n===== FIFO =====\n");

    for (int i = 0; i < TOTAL_REQUESTS; i++)
    {
        int found = 0;

        for (int j = 0; j < FRAME_COUNT; j++)
        {
            if (frames[j] == videoPages[i])
            {
                found = 1;
                hits++;
                break;
            }
        }

        if (!found)
        {
            faults++;

            frames[pointer] = videoPages[i];

            pointer = (pointer + 1) % FRAME_COUNT;
        }

        printf("Segment %d -> ", videoPages[i]);

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
}
int main()
{
    printf(" VIDEO STREAMING MEMORY SIMULATOR\n");
    printf("Page Size : %d KB\n", PAGE_SIZE);
    printf("Frames    : %d\n", FRAME_COUNT);

    return 0;
}
