/*
    GameCore Multiplayer Client
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_PORT 8080
#define BUFFER_SIZE 256

int main()
{
    int socketFD;

    struct sockaddr_in serverAddress;

    char username[50];
    char password[50];

    char loginInfo[100];
    char reply[BUFFER_SIZE];
    char message[BUFFER_SIZE];

    socketFD = socket(
        AF_INET,
        SOCK_STREAM,
        0
    );

    if (socketFD < 0)
    {
        printf("Socket creation failed.\n");

        return 1;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(SERVER_PORT);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (
        connect(
            socketFD,
            (struct sockaddr *)&serverAddress,
            sizeof(serverAddress)
        ) < 0
    )
    {
        printf("Unable to connect.\n");

        close(socketFD);

        return 1;
    }

    printf("\n===== GAMECORE CLIENT =====\n");

    printf("Username: ");
    scanf("%49s", username);

    printf("Password: ");
    scanf("%49s", password);

    sprintf(
        loginInfo,
        "%s:%s",
        username,
        password
    );

    send(
        socketFD,
        loginInfo,
        strlen(loginInfo) + 1,
        0
    );

    recv(
        socketFD,
        reply,
        sizeof(reply) - 1,
        0
    );

    printf("\nServer: %s\n", reply);

    getchar();

    printf("\nEnter message: ");

    fgets(
        message,
        sizeof(message),
        stdin
    );

    message[strcspn(message, "\n")] = '\0';

    send(
        socketFD,
        message,
        strlen(message) + 1,
        0
    );

    recv(
        socketFD,
        reply,
        sizeof(reply) - 1,
        0
    );

    printf("Server Response: %s\n", reply);

    close(socketFD);

    return 0;
}
