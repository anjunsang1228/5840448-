#include <stdio.h>
#include <string.h>

int main() {
    float num;
    unsigned int bit;
    int i;
    int result;

    printf("Input real number: ");
    result = scanf_s("%f", &num);

    if (result != 1) {
        printf("Input error\n");
        return 1;
    }

    memcpy(&bit, &num, sizeof(float));

    printf("Sign bit: %u\n", (bit >> 31) & 1);

    printf("Exponent bits: ");
    for (i = 30; i >= 23; i--) {
        printf("%u", (bit >> i) & 1);
    }
    printf("\n");

    printf("Mantissa bits: ");
    for (i = 22; i >= 0; i--) {
        printf("%u", (bit >> i) & 1);
    }
    printf("\n");

    return 0;
}
