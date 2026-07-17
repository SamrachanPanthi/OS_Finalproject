#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_FILES 10

// Login credentials
char username[] = "admin";
char password[] = "gamecore";

//  FILE STRUCTURE 

struct GameFile
{
    char name[50];
    char content[200];

    // Owner permissions
    int ownerRead;
    int ownerWrite;
    int ownerExecute;

    // Group permissions
    int groupRead;
    int groupWrite;
    int groupExecute;

    // Others permissions
    int othersRead;
    int othersWrite;
    int othersExecute;
};

struct GameFile files[MAX_FILES];

int totalFiles = 0;

//  AUDIT LOG 

void auditLog(char user[], char filename[],
              char operation[], char status[])
{
    FILE *log = fopen("audit_log.txt", "a");

    if (log == NULL)
    {
        printf("Error opening audit log file.\n");
        return;
    }

    time_t now = time(NULL);

    fprintf(log,
            "User: %s | File: %s | Operation: %s | Status: %s | Time: %s",
            user,
            filename,
            operation,
            status,
            ctime(&now));

    fclose(log);
}

// ENCRYPTION 

void encrypt(char text[])
{
    int i;

    for (i = 0; text[i] != '\0'; i++)
    {
        text[i] = text[i] + 3;
    }
}

void decrypt(char text[])
{
    int i;

    for (i = 0; text[i] != '\0'; i++)
    {
        text[i] = text[i] - 3;
    }
}

//  LOGIN 

int login()
{
    char user[30];
    char pass[30];

    printf("\n GAMECORE SECURE FILE SYSTEM \n");

    printf("Username: ");
    scanf("%29s", user);

    printf("Password: ");
    scanf("%29s", pass);

    if (strcmp(user, username) == 0 &&
        strcmp(pass, password) == 0)
    {
        printf("\nLogin Successful!\n");

        auditLog(user, "-", "LOGIN", "SUCCESS");

        return 1;
    }

    printf("\nInvalid Username or Password!\n");

    auditLog(user, "-", "LOGIN", "FAILED");

    return 0;
}

//  CREATE FILE 

void createFile()
{
    if (totalFiles >= MAX_FILES)
    {
        printf("\nStorage Full!\n");
        return;
    }

    printf("\nEnter File Name: ");
    scanf("%49s", files[totalFiles].name);

    getchar();

    printf("Enter File Content: ");

    fgets(files[totalFiles].content,
          sizeof(files[totalFiles].content),
          stdin);

    encrypt(files[totalFiles].content);

    // Owner permissions
    files[totalFiles].ownerRead = 1;
    files[totalFiles].ownerWrite = 1;
    files[totalFiles].ownerExecute = 0;

    // Group permissions
    files[totalFiles].groupRead = 1;
    files[totalFiles].groupWrite = 0;
    files[totalFiles].groupExecute = 0;

    // Others permissions
    files[totalFiles].othersRead = 0;
    files[totalFiles].othersWrite = 0;
    files[totalFiles].othersExecute = 0;

    auditLog(username,
             files[totalFiles].name,
             "CREATE",
             "SUCCESS");

    totalFiles++;

    printf("File created successfully.\n");
}

// READ FILE 

void readFile()
{
    char name[50];

    printf("\nEnter file name: ");
    scanf("%49s", name);

    int found = 0;

    for (int i = 0; i < totalFiles; i++)
    {
        if (strcmp(name, files[i].name) == 0)
        {
            found = 1;

            if (files[i].ownerRead == 0)
            {
                printf("Permission Denied!\n");

                auditLog(username,
                         name,
                         "READ",
                         "DENIED");

                return;
            }

            char temp[200];

            strcpy(temp, files[i].content);

            decrypt(temp);

            printf("\n FILE CONTENT\n");

            printf("%s\n", temp);

            auditLog(username,
                     name,
                     "READ",
                     "SUCCESS");

            return;
        }
    }

    if (!found)
    {
        printf("File not found.\n");
    }
}

//  WRITE FILE 

void writeFile()
{
    char name[50];

    printf("\nEnter file name: ");
    scanf("%49s", name);

    int found = 0;

    for (int i = 0; i < totalFiles; i++)
    {
        if (strcmp(name, files[i].name) == 0)
        {
            found = 1;

            if (files[i].ownerWrite == 0)
            {
                printf("Permission Denied!\n");

                auditLog(username,
                         name,
                         "WRITE",
                         "DENIED");

                return;
            }

            getchar();

            printf("Enter new content: ");

            fgets(files[i].content,
                  sizeof(files[i].content),
                  stdin);

            encrypt(files[i].content);

            printf("File updated successfully.\n");

            auditLog(username,
                     name,
                     "WRITE",
                     "SUCCESS");

            return;
        }
    }

    if (!found)
    {
        printf("File not found.\n");
    }
}

//  DELETE FILE 

void deleteFile()
{
    char name[50];

    printf("\nEnter file name: ");
    scanf("%49s", name);

    int found = 0;

    for (int i = 0; i < totalFiles; i++)
    {
        if (strcmp(name, files[i].name) == 0)
        {
            found = 1;

            for (int j = i; j < totalFiles - 1; j++)
            {
                files[j] = files[j + 1];
            }

            totalFiles--;

            printf("File deleted successfully.\n");

            auditLog(username,
                     name,
                     "DELETE",
                     "SUCCESS");

            return;
        }
    }

    if (!found)
    {
        printf("File not found.\n");
    }
}

//  SHOW PERMISSIONS 

void showPermissions()
{
    printf("\n FILE PERMISSIONS \n");

    if (totalFiles == 0)
    {
        printf("No files available.\n");
        return;
    }

    for (int i = 0; i < totalFiles; i++)
    {
        printf("\nFile: %s\n", files[i].name);

        printf("\nOwner Permissions\n");
        printf("Read    : %d\n", files[i].ownerRead);
        printf("Write   : %d\n", files[i].ownerWrite);
        printf("Execute : %d\n", files[i].ownerExecute);

        printf("\nGroup Permissions\n");
        printf("Read    : %d\n", files[i].groupRead);
        printf("Write   : %d\n", files[i].groupWrite);
        printf("Execute : %d\n", files[i].groupExecute);

        printf("\nOthers Permissions\n");
        printf("Read    : %d\n", files[i].othersRead);
        printf("Write   : %d\n", files[i].othersWrite);
        printf("Execute : %d\n", files[i].othersExecute);

        printf("\n\n");
    }
}

//  MAIN 

int main()
{
    int choice;

    if (!login())
    {
        return 0;
    }

    do
    {
        printf("\n===== GAMECORE FILE SYSTEM =====\n");

        printf("1. Create File\n");
        printf("2. Read File\n");
        printf("3. Write File\n");
        printf("4. Delete File\n");
        printf("5. View Permissions\n");
        printf("6. Exit\n");

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
            showPermissions();
            break;

        case 6:
            printf("\nClosing GameCore System...\n");
            break;

        default:
            printf("\nInvalid choice!\n");
        }

    } while (choice != 6);

    return 0;
}
