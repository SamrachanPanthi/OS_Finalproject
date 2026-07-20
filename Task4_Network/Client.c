#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <arpa/inet.h>

#define SERVER_PORT 8080
#include <string.h>

char username[50];
char password[50];
char loginInfo[100];
char reply[100];

printf("\nUsername: ");
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
int main()
{
    int socketFD;

    struct sockaddr_in serverAddress;

    socketFD = socket(AF_INET, SOCK_STREAM, 0);

    if (socketFD < 0)
    {
        printf("Socket creation failed.\n");
        return 1;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(SERVER_PORT);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(
            socketFD,
            (struct sockaddr *)&serverAddress,
            sizeof(serverAddress)) < 0)
    {
        printf("Connection failed.\n");

        close(socketFD);

        return 1;
    }

    printf("Connected to GameCore server.\n");

    close(socketFD);

    return 0;
}
