#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "my_math.h"

int main() {
    int num1, num2;
    printf("두 정수를 입력하세요: ");
    if (scanf("%d %d", &num1, &num2) != 2) {
        printf("입력 오류입니다.\n");
        return 1;
    }

    if (num1 == 0 && num2 == 0) {
        printf("0과 0의 GCD/LCM은 정의되지 않거나 0입니다.\n");
    }
    else {
        printf("GCD(%d, %d) = %d\n", num1, num2, get_gcd(num1, num2));
        printf("LCM(%d, %d) = %d\n", num1, num2, get_lcm(num1, num2));
    }
    return 0;
}
