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
int main()
{
    printf(" VIDEO STREAMING MEMORY SIMULATOR\n");
    printf("Page Size : %d KB\n", PAGE_SIZE);
    printf("Frames    : %d\n", FRAME_COUNT);

    return 0;
}
