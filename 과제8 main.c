#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include "fibonacci.h"

int main(void) {
    int maxN;
    int n;
    long long fib_iter, fib_recur;
    clock_t start, end;
    double time_iter, time_recur;

    printf("=============================================\n");
    printf(" 피보나치 수열 수행시간 비교 프로그램\n");
    printf(" 반복문 방식 vs 재귀 방식\n");
    printf("=============================================\n");
    printf("비교할 최대 N 값을 입력하세요: ");
    scanf("%d", &maxN);

    if (maxN < 1) {
        printf("1 이상의 정수를 입력해야 합니다.\n");
        return 1;
    }

    printf("\n");
    printf("-------------------------------------------------------------------------------\n");
    printf("%5s %15s %15s %15s %15s\n", "N", "반복문 값", "재귀 값", "반복문 시간", "재귀 시간");
    printf("-------------------------------------------------------------------------------\n");

    for (n = 1; n <= maxN; n++) {
        start = clock();
        fib_iter = fibonacci_iterative(n);
        end = clock();
        time_iter = (double)(end - start) / CLOCKS_PER_SEC;

        start = clock();
        fib_recur = fibonacci_recursive(n);
        end = clock();
        time_recur = (double)(end - start) / CLOCKS_PER_SEC;

        printf("%5d %15lld %15lld %15.8f %15.8f\n",
            n, fib_iter, fib_recur, time_iter, time_recur);
    }

    printf("-------------------------------------------------------------------------------\n");

    printf("\n[분석]\n");
    printf("1. 반복문 방식은 중복 계산이 없어서 빠릅니다.\n");
    printf("2. 재귀 방식은 같은 값을 여러 번 계산하므로 느립니다.\n");
    printf("3. N이 커질수록 재귀 방식의 수행시간이 급격히 증가합니다.\n");

    return 0;
}