#include <stdio.h>

void checkEndianness() {
    unsigned int num = 1;
    char *byte = (char*)&num;

    if (*byte) {
        printf("The host machine is Little Endian.\n");
    } else {
        printf("The host machine is Big Endian.\n");
    }
}

void printBytes(unsigned int number) {
    unsigned char *bytes = (unsigned char*)&number;

    printf("Byte 0: %02X\n", bytes[0]);
    printf("Byte 1: %02X\n", bytes[1]);
    printf("Byte 2: %02X\n", bytes[2]);
    printf("Byte 3: %02X\n", bytes[3]);
}

unsigned int convertEndianness(unsigned int number) {
    return ((number >> 24) & 0xFF) |
           ((number >> 8) & 0xFF00) |
           ((number << 8) & 0xFF0000) |
           ((number << 24) & 0xFF000000);
}

int main() {
    unsigned int number;

    checkEndianness();

    printf("Enter an unsigned integer: ");
    scanf("%u", &number);

    printf("Original number byte content:\n");
    printBytes(number);

    unsigned int converted_number = convertEndianness(number);

    printf("Converted number: %u\n", converted_number);
    printf("Converted number byte content:\n");
    printBytes(converted_number);

    return 0;
}
