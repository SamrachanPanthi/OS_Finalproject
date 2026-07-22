/*
    GameCore Operating System

    Features:
    - TCP socket communication
    - Player connection handling
    - Player authentication
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>

#define PORT 8080

void authenticatePlayer(int clientSocket)
{
    char loginData[100];

    char username[50];

    char password[50];

    int received = recv(
        clientSocket,
        loginData,
        sizeof(loginData) - 1,
        0
    );

    if (received <= 0)
    {
        printf("Login data not received.\n");

        close(clientSocket);

        return;
    }

    loginData[received] = '\0';

    sscanf(
        loginData,
        "%[^:]:%s",
        username,
        password
    );

    printf(
        "\nUsername: %s\n",
        username
    );

    printf(
        "Password: %s\n",
        password
    );

    if (
        strcmp(username, "player") == 0 &&
        strcmp(password, "gamecore123") == 0
    )
    {
        char success[] =
            "Authentication Successful";

        send(
            clientSocket,
            success,
            strlen(success) + 1,
            0
        );

        printf(
            "Player authenticated.\n"
        );
    }

    else
    {
        char fail[] =
            "Access Denied";

        send(
            clientSocket,
            fail,
            strlen(fail) + 1,
            0
        );

        printf(
            "Authentication failed.\n"
        );
    }
}

int main()
{
    int serverSocket;

    int clientSocket;

    struct sockaddr_in serverAddress;

    struct sockaddr_in clientAddress;

    socklen_t clientLength =
        sizeof(clientAddress);

    serverSocket = socket(
        AF_INET,
        SOCK_STREAM,
        0
    );

    if (serverSocket < 0)
    {
        printf(
            "Socket creation failed.\n"
        );

        return 1;
    }

    printf(
        "GameCore server socket created.\n"
    );

    serverAddress.sin_family =
        AF_INET;

    serverAddress.sin_addr.s_addr =
        INADDR_ANY;

    serverAddress.sin_port =
        htons(PORT);

    if (
        bind(
            serverSocket,
            (struct sockaddr *)&serverAddress,
            sizeof(serverAddress)
        ) < 0
    )
    {
        printf(
            "Bind failed.\n"
        );

        close(serverSocket);

        return 1;
    }

    printf(
        "Server running on port %d\n",
        PORT
    );

    if (
        listen(
            serverSocket,
            5
        ) < 0
    )
    {
        printf(
            "Listen failed.\n"
        );

        close(serverSocket);

        return 1;
    }

    printf(
        "Waiting for players...\n"
    );

    while (1)
    {
        clientSocket = accept(
            serverSocket,
            (struct sockaddr *)&clientAddress,
            &clientLength
        );

        if (clientSocket < 0)
        {
            printf(
                "Connection failed.\n"
            );

            continue;
        }

        printf(
            "\nPlayer connected.\n"
        );

        authenticatePlayer(
            clientSocket
        );

        close(
            clientSocket
        );
    }

    close(
        serverSocket
    );

    return 0;
}
