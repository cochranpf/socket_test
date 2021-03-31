#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 8080
#define BUFF_SIZE 1024

int main (int argc, const char *argv[]){
    int sock_desc;
    struct sockaddr_in server_addr;
    char buffer[BUFF_SIZE];

    if ((sock_desc = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("failed to create socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    //converts IP address to binary form and sets server_addr.sin_addr
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0){
        perror("invalid address");
        exit(EXIT_FAILURE);
    }

    if (connect(sock_desc, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        perror("failed to connect");
        exit(EXIT_FAILURE);
    }
    printf("connect to server\n");

    char *message = "bruh hey what up";
    strncpy(buffer, message, strlen(message));

    send(sock_desc, buffer, strlen(buffer), 0);

    printf("sent message\n");

    close(sock_desc);
    return 0;
}