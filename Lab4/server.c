#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    int port = atoi(argv[1]);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    getpeername(new_socket, (struct sockaddr*)&client_addr, &client_addr_len);
    printf("Client IP: %s\n", inet_ntoa(client_addr.sin_addr));
    printf("Client Port: %d\n", ntohs(client_addr.sin_port));

    while (1) {
        int valread = read(new_socket, buffer, BUFFER_SIZE);
        if (valread <= 0) {
            perror("read error or client disconnected");
            break;
        }
        printf("Message from client: %s\n", buffer);

        if (strcmp(buffer, "close") == 0) {
            printf("Connection closed by client.\n");
            break;
        }

        // Server input handling
        char response[BUFFER_SIZE];
        printf("Enter response message: ");
        fgets(response, BUFFER_SIZE, stdin);
        response[strcspn(response, "\n")] = '\0';
        send(new_socket, response, strlen(response), 0);

        memset(buffer, 0, BUFFER_SIZE);
    }

    close(new_socket);
    close(server_fd);
    return 0;
}
