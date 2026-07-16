#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char username[] = "admin";
char password[] = "gamecore";
#define MAX_FILES 10

struct GameFile
{
    char name[50];
    char content[200];
};

struct GameFile files[MAX_FILES];

int totalFiles = 0;
int login()
{
    char user[30];
    char pass[30];

    printf("\n GAMECORE SECURE FILE SYSTEM \n");

    printf("Username: ");
    scanf("%s", user);

    printf("Password: ");
    scanf("%s", pass);

    if (strcmp(user, username) == 0 &&
        strcmp(pass, password) == 0)
    {
        printf("\nLogin Successful!\n");
        return 1;
    }

    printf("\nInvalid Username or Password!\n");

    return 0;
}
void createFile()
{
    if (totalFiles >= MAX_FILES)
    {
        printf("\nStorage Full!\n");
        return;
    }

    printf("\nEnter File Name: ");
    scanf("%s", files[totalFiles].name);

    getchar();

    printf("Enter File Content: ");

    fgets(files[totalFiles].content,
          sizeof(files[totalFiles].content),
          stdin);

    totalFiles++;

    printf("File created successfully.\n");
}

void deleteFile()
{
    char name[50];

    printf("\nEnter file name: ");
    scanf("%s", name);

    for (int i = 0; i < totalFiles; i++)
    {
        if (strcmp(name, files[i].name) == 0)
        {
            for (int j = i; j < totalFiles - 1; j++)
            {
                files[j] = files[j + 1];
            }

            totalFiles--;

            printf("File deleted successfully.\n");

            return;
        }
    }

    printf("File not found.\n");
}
void readFile()
{
    char name[50];

    printf("\nEnter file name: ");
    scanf("%s", name);

    for (int i = 0; i < totalFiles; i++)
    {
        if (strcmp(name, files[i].name) == 0)
        {
            printf("\n===== FILE CONTENT =====\n");

            printf("%s\n", files[i].content);

            return;
        }
    }

    printf("File not found.\n");
}

void writeFile()
{
    char name[50];

    printf("\nEnter file name: ");
    scanf("%s", name);

    for (int i = 0; i < totalFiles; i++)
    {
        if (strcmp(name, files[i].name) == 0)
        {
            getchar();

            printf("Enter new content: ");

            fgets(files[i].content,
                  sizeof(files[i].content),
                  stdin);

            printf("File updated successfully.\n");

            return;
        }
    }

    printf("File not found.\n");
}
int main()
{
    int choice;

    if (!login())
    {
        return 0;
    }

    do
    {
        printf("\n1. Create File");
        printf("\n2. Read File");
        printf("\n3. Write File");
        printf("\n4. Delete File");
        printf("\n5. Exit");

        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                createFile();
                break;

            case 2:
                readFile();
                break;

            case 3:
                writeFile();
                break;

            case 4:
                deleteFile();
                break;

            case 5:
                printf("\nExiting...\n");
                break;

            default:
                printf("\nInvalid choice!\n");
        }

    } while (choice != 5);

    return 0;
}
