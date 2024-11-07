#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080

void error_exit(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[1024];
    int expected_sequence = 0;
    socklen_t addr_len = sizeof(client_addr);

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        error_exit("Socket creation failed");
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        error_exit("Bind failed");
    }

    while (1) {
        int n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, &addr_len);
        buffer[n] = '\0';
        printf("Server: Received %s\n", buffer);

        int received_sequence = atoi(buffer + 7);
        if (received_sequence == expected_sequence) {
            printf("Server: Sending ACK for packet %d\n", expected_sequence);
            snprintf(buffer, sizeof(buffer), "%d", expected_sequence);
            sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&client_addr, addr_len);
            expected_sequence++;
        } else {
            printf("Server: Out-of-order packet received, ignoring.\n");
        }
    }

    close(sockfd);
    return 0;
}
