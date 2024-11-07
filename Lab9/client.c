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

void client() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[DATA_SIZE];
    memset(buffer, 'A', sizeof(buffer));

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    int num_fragments = (DATA_SIZE + (MTU_SIZE - HEADER_SIZE) - 1) / (MTU_SIZE - HEADER_SIZE);
    printf("Total fragments: %d\n", num_fragments);

    for (int i = 0; i < num_fragments; i++) {
        Fragment fragment;
        fragment.id = 1;
        fragment.flag = (i < num_fragments - 1) ? 1 : 0;
        fragment.offset = i * (MTU_SIZE - HEADER_SIZE);
        fragment.hl = HEADER_SIZE;
        fragment.tl = MTU_SIZE;

        int bytes_to_copy = MTU_SIZE - HEADER_SIZE;
        if (fragment.offset + bytes_to_copy > DATA_SIZE) {
            bytes_to_copy = DATA_SIZE - fragment.offset;
        }
        memcpy(fragment.payload, buffer + fragment.offset, bytes_to_copy);

        if (send(sockfd, &fragment, sizeof(Fragment), 0) < 0) {
            perror("Send failed");
            exit(EXIT_FAILURE);
        }

        printf("Sent fragment %d with offset %d\n", i + 1, fragment.offset);
    }

    close(sockfd);
}

int main() {
    client();
    return 0;
}
