#include <stdio.h>
#include <stdint.h>

int main() 
// 8비트 부호 있는 정수 -1을 선언 (2의 보수라면 11111111, 1의 보수라면 11111110)
{

    int8_t val = -1;
 // val의 메모리 주소를 unsigned char 포인터로 형변환하여 1바이트씩 접근할 수 있게 함
    unsigned char* ptr = (unsigned char*)&val;
 // 해당 메모리 위치에 저장된 값을 16진수 형식(%02X)으로 출력
    printf("정수 -1의 메모리 값 (16진수): 0x%02X\n", *ptr);
// 2의 보수 방식에서는 -1이 0xFF(모든 비트가 1)로 표현됨
    if (*ptr == 0xFF) 
        printf("결과: 2의 보수입니다. \n");
// 1의 보수 방식에서는 -1이 0xFE(마지막 비트만 0)로 표현됨
    else if (*ptr == 0xFE) 
        printf("결과: 1의 보수입니다. \n");
    

    return 0;

}



