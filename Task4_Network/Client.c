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

    char message[BUFFER_SIZE];
    char reply[BUFFER_SIZE];



    //Create socket 

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

    printf(
        "Client socket created successfully.\n"
    );



    // Configure server address 

    serverAddress.sin_family =
        AF_INET;

    serverAddress.sin_port =
        htons(SERVER_PORT);

    serverAddress.sin_addr.s_addr =
        inet_addr("127.0.0.1");



    // Connect to server 

    if (
        connect(
            socketFD,
            (struct sockaddr *)&serverAddress,
            sizeof(serverAddress)
        ) < 0
    )
    {
        printf(
            "Unable to connect to server.\n"
        );

        close(socketFD);

        return 1;
    }

    printf(
        "\nConnected to GameCore server.\n"
    );



    // Login section 

    printf(
        "\n GAMECORE CLIENT \n"
    );

    printf("Username: ");
    scanf("%49s", username);

    printf("Password: ");
    scanf("%49s", password);



    // Create login packet

    sprintf(
        loginInfo,
        "%s:%s",
        username,
        password
    );



    // Send authentication data 

    if (
        send(
            socketFD,
            loginInfo,
            strlen(loginInfo) + 1,
            0
        ) < 0
    )
    {
        printf(
            "Failed to send login information.\n"
        );

        close(socketFD);

        return 1;
    }



    // Receive authentication result

    int received = recv(
        socketFD,
        reply,
        sizeof(reply) - 1,
        0
    );

    if (received <= 0)
    {
        printf(
            "Server not responding.\n"
        );

        close(socketFD);

        return 1;
    }

    reply[received] = '\0';

    printf(
        "\nServer: %s\n",
        reply
    );



    /* Access denied */

    if (
        strcmp(
            reply,
            "Access Denied"
        ) == 0
    )
    {
        close(socketFD);

        return 1;
    }



    getchar();



    printf("\nAvailable Commands:\n");

    printf(
        "START_GAME\n"
    );

    printf(
        "STATUS\n"
    );

    printf(
        "SCORE <points>\n"
    );

    printf(
        "CHAT <message>\n"
    );

    printf(
        "QUIT\n"
    );



    /* Communication loop */

    while (1)
    {
        printf(
            "\nEnter Command: "
        );

        fgets(
            message,
            sizeof(message),
            stdin
        );



        message[
            strcspn(
                message,
                "\n"
            )
        ] = '\0';



        /* Validate empty input */

        if (
            strlen(message) == 0
        )
        {
            printf(
                "Empty command not allowed.\n"
            );

            continue;
        }



        /* Send message */

        if (
            send(
                socketFD,
                message,
                strlen(message) + 1,
                0
            ) < 0
        )
        {
            printf(
                "Message transmission failed.\n"
            );

            break;
        }



        /* Receive server reply */

        received = recv(
            socketFD,
            reply,
            sizeof(reply) - 1,
            0
        );

        if (received <= 0)
        {
            printf(
                "Connection lost.\n"
            );

            break;
        }

        reply[received] = '\0';



        printf(
            "Server Response: %s\n",
            reply
        );



        /* Disconnect */

        if (
            strcmp(
                message,
                "QUIT"
            ) == 0
        )
        {
            break;
        }
    }



    close(socketFD);

    printf(
        "\nDisconnected from GameCore server.\n"
    );

    return 0;
}
