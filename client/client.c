#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <time.h>

int getRandom(int lower, int upper, int count)
{
    int i;
    int num;

    for (i = 0; i < count; i++)
    {
        num = (rand() % (upper - lower + 1)) + lower;
    }

    return num;
}

char *getColor(int number)
{
    switch (number)
    {
    case 0:
        return "\x1b[31m";
    case 1:
        return "\x1b[32m";
    case 2:
        return "\x1b[33m";
    case 3:
        return "\x1b[34m";
    case 4:
        return "\x1b[35m";
    }

    return "aa";
}

int main(void)
{
    char message[1000];
    struct sockaddr_in server;
    int fd;
    char aux[1500];
    char name[50];
    int color;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(8096);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);
    connect(fd, (struct sockaddr *)&server, sizeof(server));

    srand(time(0));

    color = getRandom(0, 4, 1);

    printf("Say your name: ");
    fgets(name, 50, stdin);

    strtok(name, "\n");

    while (1)
    {
        printf("Enter a message: ");
        fgets(message, 100, stdin);

        strcpy(aux, getColor(color));
        strcat(aux, name);
        strcat(aux, "\x1b[0m");
        strcat(aux, " say: ");
        strcat(aux, message);

        send(fd, aux, strlen(aux), 0);
    }
}