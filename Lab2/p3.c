#include <stdio.h>

int main() {
    unsigned int number;
    unsigned char byte1, byte2, byte3, byte4;

    printf("Enter an unsigned integer: ");
    scanf("%u", &number);

    byte1 = (number & 0xFF);
    byte2 = (number >> 8) & 0xFF;
    byte3 = (number >> 16) & 0xFF;
    byte4 = (number >> 24) & 0xFF;

    printf("Byte 1: %u\n", byte1);
    printf("Byte 2: %u\n", byte2);
    printf("Byte 3: %u\n", byte3);
    printf("Byte 4: %u\n", byte4);

    return 0;
}
