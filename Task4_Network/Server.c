#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define BUFFER_SIZE 256


void *clientHandler(void *socketPointer)
{
    int clientSocket = *(int *)socketPointer;

    free(socketPointer);

    char buffer[BUFFER_SIZE];

    char username[50];
    char password[50];

    char loginData[100];


    /* Receive login information */

    int loginReceived = recv(
        clientSocket,
        loginData,
        sizeof(loginData) - 1,
        0
    );

    if (loginReceived <= 0)
    {
        printf("Login data not received.\n");

        close(clientSocket);

        pthread_exit(NULL);
    }

    loginData[loginReceived] = '\0';


    /* Extract username and password */

    if (
        sscanf(
            loginData,
            "%49[^:]:%49s",
            username,
            password
        ) != 2
    )
    {
        char invalid[] = "Invalid Login Format";

        send(
            clientSocket,
            invalid,
            strlen(invalid) + 1,
            0
        );

        close(clientSocket);

        pthread_exit(NULL);
    }


    printf("\n PLAYER CONNECTED \n");

    printf("Username: %s\n", username);


    /* Authentication */

    if (
        strcmp(username, "player") == 0 &&
        strcmp(password, "gamecore123") == 0
    )
    {
        char success[] = "Authentication Successful";

        send(
            clientSocket,
            success,
            strlen(success) + 1,
            0
        );

        printf("Player authenticated.\n");
    }
    else
    {
        char fail[] = "Access Denied";

        send(
            clientSocket,
            fail,
            strlen(fail) + 1,
            0
        );

        printf("Authentication failed.\n");

        close(clientSocket);

        pthread_exit(NULL);
    }


    /* Game communication loop */

    while (1)
    {
        memset(
            buffer,
            0,
            sizeof(buffer)
        );

        int received = recv(
            clientSocket,
            buffer,
            sizeof(buffer) - 1,
            0
        );

        if (received <= 0)
        {
            printf("Player disconnected.\n");

            break;
        }

        buffer[received] = '\0';

        printf(
            "Player Command: %s\n",
            buffer
        );

        char response[BUFFER_SIZE];


        /* Start game */

        if (strcmp(buffer, "START_GAME") == 0)
        {
            strcpy(
                response,
                "Game Started Successfully"
            );
        }


        /* Score update */

        else if (
            strncmp(
                buffer,
                "SCORE",
                5
            ) == 0
        )
        {
            strcpy(
                response,
                "Score Updated"
            );
        }


        /* Player status */

        else if (
            strcmp(
                buffer,
                "STATUS"
            ) == 0
        )
        {
            strcpy(
                response,
                "Player Status: Active | Health: 100"
            );
        }


        /* Chat message */

        else if (
            strncmp(
                buffer,
                "CHAT",
                4
            ) == 0
        )
        {
            strcpy(
                response,
                "Message Delivered To Players"
            );
        }


        /* Disconnect */

        else if (
            strcmp(
                buffer,
                "QUIT"
            ) == 0
        )
        {
            strcpy(
                response,
                "Disconnected From GameCore Server"
            );

            send(
                clientSocket,
                response,
                strlen(response) + 1,
                0
            );

            break;
        }


        /* Invalid command */

        else
        {
            strcpy(
                response,
                "Invalid Game Command"
            );
        }


        send(
            clientSocket,
            response,
            strlen(response) + 1,
            0
        );
    }


    close(clientSocket);

    pthread_exit(NULL);
}


int main()
{
    int serverSocket;
    int clientSocket;

    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;

    socklen_t clientLength =
        sizeof(clientAddress);


    /* Create socket */

    serverSocket = socket(
        AF_INET,
        SOCK_STREAM,
        0
    );

    if (serverSocket < 0)
    {
        printf("Socket creation failed.\n");

        return 1;
    }

    printf(
        "GameCore server socket created.\n"
    );


    /* Configure server */

    serverAddress.sin_family =
        AF_INET;

    serverAddress.sin_addr.s_addr =
        INADDR_ANY;

    serverAddress.sin_port =
        htons(PORT);


    /* Bind */

    if (
        bind(
            serverSocket,
            (struct sockaddr *)&serverAddress,
            sizeof(serverAddress)
        ) < 0
    )
    {
        printf("Bind failed.\n");

        close(serverSocket);

        return 1;
    }

    printf(
        "Server running on port %d\n",
        PORT
    );


    /* Listen */

    if (
        listen(
            serverSocket,
            5
        ) < 0
    )
    {
        printf("Listen failed.\n");

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


        int *newSocket =
            malloc(sizeof(int));

        *newSocket = clientSocket;


        pthread_t thread;

        pthread_create(
            &thread,
            NULL,
            clientHandler,
            newSocket
        );

        pthread_detach(thread);
    }


    close(serverSocket);

    return 0;
}
