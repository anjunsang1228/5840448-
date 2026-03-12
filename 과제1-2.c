#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
    double input;
    printf("Enter number: ");
    scanf ("%lf", &input);

    // 실수를 256을 곱해 16비트 정수로 변환 (Q8.8)
    unsigned short bits = (unsigned short)(short)(input * 256);

    printf("Result: ");
    for (int i = 15; i >= 0; i--) {
        // i번째 비트가 1인지 0인지 출력
        printf("%d", (bits >> i) & 1);

        // 8번째 비트 뒤에 소수점 찍기
        if (i == 8) printf(".");
    }
    printf("\n");

    return 0;
}