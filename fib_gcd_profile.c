#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include "gcd.h"

long long fib_calls = 0;
int gcd_steps = 0;

long long fib(int n) {
    fib_calls++;

    if (n <= 1)
        return n;

    return fib(n - 1) + fib(n - 2);
}

int gcd_count_steps(int a, int b) {
    gcd_steps = 0;

    while (b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
        gcd_steps++;
    }

    return a;
}

int main(void) {
    FILE* fp;
    int n;

    fp = fopen("fib_gcd_profile.csv", "w");
    if (fp == NULL) {
        printf("CSV 파일을 열 수 없습니다.\n");
        return 1;
    }

    fprintf(fp, "n,F(n),F(n-1),GCD,fib_calls,gcd_steps,cpu_time_sec\n");

    printf(" n |        F(n) |      F(n-1) | GCD | fib_calls | gcd_steps | cpu_time_sec\n");
    printf("-------------------------------------------------------------------------------\n");

    for (n = 5; n <= 30; n++) {
        long long fn, fn1;
        int result_gcd;
        clock_t start, end;
        double cpu_time;

        fib_calls = 0;

        start = clock();

        fn = fib(n);
        fn1 = fib(n - 1);
        result_gcd = gcd_count_steps((int)fn, (int)fn1);

        end = clock();

        cpu_time = (double)(end - start) / CLOCKS_PER_SEC;

        printf("%2d | %12lld | %12lld | %3d | %9lld | %9d | %12f\n",
            n, fn, fn1, result_gcd, fib_calls, gcd_steps, cpu_time);

        fprintf(fp, "%d,%lld,%lld,%d,%lld,%d,%f\n",
            n, fn, fn1, result_gcd, fib_calls, gcd_steps, cpu_time);
    }

    fclose(fp);

    printf("\n실험 결과가 fib_gcd_profile.csv 파일로 저장되었습니다.\n");

    return 0;
}