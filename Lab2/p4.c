#include <stdio.h>

struct pkt {
    char ch1;
    char ch2[2];
    char ch3;
};

int main() {
    struct pkt packet;
    unsigned int number;
    unsigned int reconstructed_number;

    printf("Enter an integer (0 to 255): ");
    scanf("%u", &number);

    if (number > 255) {
        printf("Number out of range. Please enter a number between 0 and 255.\n");
        return 1;
    }

    packet.ch1 = (number & 0xFF);
    packet.ch2[0] = (number >> 8) & 0xFF;
    packet.ch2[1] = (number >> 16) & 0xFF;
    packet.ch3 = (number >> 24) & 0xFF;

    printf("ch1: %u\n", (unsigned char)packet.ch1);
    printf("ch2[0]: %u\n", (unsigned char)packet.ch2[0]);
    printf("ch2[1]: %u\n", (unsigned char)packet.ch2[1]);
    printf("ch3: %u\n", (unsigned char)packet.ch3);

    reconstructed_number = (packet.ch3 << 24) |
                           (packet.ch2[1] << 16) |
                           (packet.ch2[0] << 8) |
                           packet.ch1;

    printf("Reconstructed Number: %u\n", reconstructed_number);

    return 0;
}
