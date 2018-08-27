#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

void main()
{
    struct sockaddr_in serv; //This is our main socket variable.
    int fd;                  //This is the socket file descriptor that will be used to identify the socket
    int conn;                //This is the connection file descriptor that will be used to distinguish client connections.
    char message[1000] = ""; //This array will store the messages that are sent by the server

    serv.sin_family = AF_INET;
    serv.sin_port = htons(8096); //Define the port at which the server will listen for connections.
    serv.sin_addr.s_addr = INADDR_ANY;
    fd = socket(AF_INET, SOCK_STREAM, 0); //This will create a new socket and also return the identifier of the socket into fd.
    // To handle errors, you can add an if condition that checks whether fd is greater than 0. If it isn't, prompt an error
    bind(fd, (struct sockaddr *)&serv, sizeof(serv)); //assigns the address specified by serv to the socket
    listen(fd, 5);                                    //Listen for client connections. Maximum 5 connections will be permitted.
    //Now we start handling the connections.
    while (conn = accept(fd, (struct sockaddr *)NULL, NULL))
    {
        printf("New user connected!\n");

        int pid;
        if ((pid = fork()) == 0)
        {
            while (recv(conn, message, 1000, 0) > 0)
            {
                printf("> %s", message);
                memset(message, 0x00, sizeof(message));
            }
            exit(0);
        }
    }
}