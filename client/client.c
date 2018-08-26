#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>

int main(void)
{
    char *message[1000];
    struct sockaddr_in server;
    int fd;
    char *aux[1500];
    char *name[50];

    fd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(8096);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);       //This binds the client to localhost
    connect(fd, (struct sockaddr *)&server, sizeof(server)); //This connects the client to the server.

    printf("Say your name: ");
    fgets(name, 50, stdin);

    strtok(name, "\n");

    while (1)
    {
        printf("Enter a message: ");
        fgets(message, 100, stdin);

        strcpy(aux, name);
        strcat(aux, " say: ");
        strcat(aux, message);

        send(fd, aux, strlen(aux), 0);
    }
}