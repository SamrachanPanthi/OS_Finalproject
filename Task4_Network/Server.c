#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>


#define PORT 8080



int main()
{

    int serverSocket;


    struct sockaddr_in serverAddress;



    // Create TCP socket

    serverSocket =
    socket(
        AF_INET,
        SOCK_STREAM,
        0
    );



    if(serverSocket < 0)
    {

        printf(
        "Socket creation failed.\n"
        );

        return 1;

    }



    printf(
    "GameCore Server Socket Created\n"
    );



    serverAddress.sin_family =
    AF_INET;


    serverAddress.sin_addr.s_addr =
    INADDR_ANY;


    serverAddress.sin_port =
    htons(PORT);




    // Bind server

    if(bind(
        serverSocket,
        (struct sockaddr *)&serverAddress,
        sizeof(serverAddress)
    ) < 0)
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




    // Listen

    listen(
        serverSocket,
        5
    );



    printf(
    "Waiting for players...\n"
    );



    close(serverSocket);


    return 0;

}
