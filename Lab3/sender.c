#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <receiver_ip> <receiver_port> <sender_port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *receiver_ip = argv[1];
    int receiver_port = atoi(argv[2]);
    int sender_port = atoi(argv[3]);

    int sockfd;
    struct sockaddr_in receiver_addr, sender_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(receiver_addr);

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&sender_addr, 0, sizeof(sender_addr));
    sender_addr.sin_family = AF_INET;
    sender_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    sender_addr.sin_port = htons(sender_port);

    if (bind(sockfd, (struct sockaddr *)&sender_addr, sizeof(sender_addr)) < 0) {
        perror("bind");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    memset(&receiver_addr, 0, sizeof(receiver_addr));
    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_addr.s_addr = inet_addr(receiver_ip);
    receiver_addr.sin_port = htons(receiver_port);

    while (1) {
        printf("Enter message to send: ");
        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            perror("fgets");
            break;
        }
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove newline character

        if (sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&receiver_addr, sizeof(receiver_addr)) < 0) {
            perror("sendto");
            break;
        }

        if (strcmp(buffer, "exit") == 0) {
            break;
        }

        ssize_t recv_len = recvfrom(sockfd, buffer, BUFFER_SIZE - 1, 0, (struct sockaddr *)&receiver_addr, &addr_len);
        if (recv_len < 0) {
            perror("recvfrom");
            break;
        }

        buffer[recv_len] = '\0';  // Null terminate the received message
        printf("Received message: %s\n", buffer);

        if (strcmp(buffer, "exit") == 0) {
            break;
        }
    }

    close(sockfd);
    return 0;
}
