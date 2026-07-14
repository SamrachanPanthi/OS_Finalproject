#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char username[] = "admin";
char password[] = "gamecore";

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

int main()
{
    if (!login())
    {
        return 0;
    }

    printf("\nWelcome to GameCore!\n");

    return 0;
}
