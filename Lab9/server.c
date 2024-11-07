#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MTU_SIZE 512
#define HEADER_SIZE 20
#define DATA_SIZE 4096

typedef struct {
    int id;
    int flag;
    int offset;
    int hl;
    int tl;
    char payload[MTU_SIZE - HEADER_SIZE];
} Fragment;

void server() {
    int sockfd, newsockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    Fragment fragment;
    char reassembled_data[DATA_SIZE];
    int received_fragments = 0;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    listen(sockfd, 5);
    printf("Waiting for client to connect...\n");

    newsockfd = accept(sockfd, (struct sockaddr*)&client_addr, &addr_len);
    if (newsockfd < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    memset(reassembled_data, 0, sizeof(reassembled_data));

    while (1) {
        int bytes_received = recv(newsockfd, &fragment, sizeof(Fragment), 0);
        if (bytes_received <= 0) break;

        printf("Received fragment with offset %d, flag %d\n", fragment.offset, fragment.flag);
        memcpy(reassembled_data + fragment.offset, fragment.payload, MTU_SIZE - HEADER_SIZE);
        received_fragments++;

        if (fragment.flag == 0) break;
    }

    printf("Reassembled data: %.*s\n", DATA_SIZE, reassembled_data);

    close(newsockfd);
    close(sockfd);
}

int main() {
    server();
    return 0;
}
