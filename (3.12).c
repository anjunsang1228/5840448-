#include <stdio.h>
#include <stdint.h>

int main() {

    int8_t val = -1;

    unsigned char* ptr = (unsigned char*)&val;

    printf("정수 -1의 메모리 값 (16진수): 0x%02X\n", *ptr);

    if (*ptr == 0xFF) {
        printf("결과: 현재 시스템은 2의 보수(Two's Complement) 방식을 사용하고 있습니다.\n");
    }
    else if (*ptr == 0xFE) {
        printf("결과: 현재 시스템은 1의 보수(One's Complement) 방식을 사용하고 있습니다.\n");
    }
    else {
        printf("결과: 알 수 없는 방식이거나 부호 절대치 방식입니다.\n");
    }

    return 0;
}