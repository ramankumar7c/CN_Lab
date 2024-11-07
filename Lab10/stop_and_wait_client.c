#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>

#define PORT 8080
#define TIMEOUT_SEC 2

void error_exit(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[1024];
    int sequence_number = 0;
    socklen_t addr_len = sizeof(server_addr);

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        error_exit("Socket creation failed");
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    struct timeval timeout = {TIMEOUT_SEC, 0};
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

    for (int i = 0; i < 5; i++) {
        snprintf(buffer, sizeof(buffer), "Packet %d", sequence_number);

        int ack_received = 0;
        while (!ack_received) {
            printf("Client: Sending %s\n", buffer);
            sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, addr_len);

            char ack[1024];
            int n = recvfrom(sockfd, ack, sizeof(ack), 0, (struct sockaddr *)&server_addr, &addr_len);
            if (n > 0 && atoi(ack) == sequence_number) {
                printf("Client: Received ACK for packet %d\n", sequence_number);
                ack_received = 1;
                sequence_number++;
            } else {
                printf("Client: Timeout or incorrect ACK, retransmitting...\n");
            }
        }
    }

    close(sockfd);
    return 0;
}
