#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFF_SIZE 1024

int main (int argc, const char *argv[]){
    int socket_desc, socket_acc;
    struct sockaddr_in address;
    int addr_len = sizeof(address);
    char buffer[BUFF_SIZE];

    int opt = 1;

    if ((socket_desc = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(socket_desc, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
        perror("failed to set socket options");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(socket_desc, (struct sockaddr *)&address, sizeof(address)) < 0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    printf("listening...\n");
    if (listen(socket_desc, 3) < 0){
        perror("listen failure");
        exit(EXIT_FAILURE);
    }
    if ((socket_acc = accept(socket_desc, (struct sockaddr *)&address, (socklen_t *)&addr_len)) < 0){
        perror("accept error");
        exit(EXIT_FAILURE);
    }

    int message = read(socket_acc, buffer, BUFF_SIZE);
    printf("%s", buffer);

    close(socket_desc);
    return 0;
}