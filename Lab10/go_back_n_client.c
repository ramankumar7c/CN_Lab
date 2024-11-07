#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>

#define PORT 8080
#define TIMEOUT_SEC 2
#define WINDOW_SIZE 3
#define TOTAL_PACKETS 10

void error_exit(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[1024];
    int base = 0, next_seq = 0;
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

    while (base < TOTAL_PACKETS) {
        while (next_seq < base + WINDOW_SIZE && next_seq < TOTAL_PACKETS) {
            snprintf(buffer, sizeof(buffer), "Packet %d", next_seq);
            printf("Client: Sending %s\n", buffer);
            sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, addr_len);
            next_seq++;
        }

        char ack[1024];
        int ack_num;
        int n = recvfrom(sockfd, ack, sizeof(ack), 0, (struct sockaddr *)&server_addr, &addr_len);
        if (n > 0) {
            ack_num = atoi(ack);
            printf("Client: Received ACK for packet %d\n", ack_num);
            base = ack_num + 1;
        } else {
            printf("Client: Timeout, resending window from packet %d\n", base);
            next_seq = base;
        }
    }

    close(sockfd);
    return 0;
}
