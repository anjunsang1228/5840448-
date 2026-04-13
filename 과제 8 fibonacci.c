#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include "fibonacci.h"

long long fibonacci_iterative(int n)
{
    long long prev = 1, curr = 1, next;
    int i;

    if (n == 1 || n == 2)
        return 1;

    for (i = 3; i <= n; i++)
    {
        next = prev + curr;
        prev = curr;
        curr = next;
    }

    return curr;
}

long long fibonacci_recursive(int n)
{
    if (n == 1 || n == 2)
        return 1;

    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

double measure_iterative_time(int n)
{
    clock_t start, end;

    start = clock();
    fibonacci_iterative(n);
    end = clock();

    return (double)(end - start) / CLOCKS_PER_SEC;
}

double measure_recursive_time(int n)
{
    clock_t start, end;

    start = clock();
    fibonacci_recursive(n);
    end = clock();

    return (double)(end - start) / CLOCKS_PER_SEC;
}

void print_result_table(int start_n, int end_n)
{
    int n;
    long long iterative_value, recursive_value;
    double iterative_time, recursive_time;

    printf("===============================================================\n");
    printf("  N\t반복문 결과\t재귀 결과\t반복문 시간\t재귀 시간\n");
    printf("===============================================================\n");

    for (n = start_n; n <= end_n; n++)
    {
        iterative_value = fibonacci_iterative(n);
        recursive_value = fibonacci_recursive(n);
        iterative_time = measure_iterative_time(n);
        recursive_time = measure_recursive_time(n);

        printf("%3d\t%10lld\t%10lld\t%10.6f\t%10.6f\n",
            n, iterative_value, recursive_value, iterative_time, recursive_time);
    }
}

void save_markdown_report(const char* filename, int start_n, int end_n)
{
    FILE* fp;
    int n;
    long long iterative_value, recursive_value;
    double iterative_time, recursive_time;

    fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("파일을 생성할 수 없습니다.\n");
        return;
    }

    fprintf(fp, "# 피보나치 수열 수행시간 비교\n\n");
    fprintf(fp, "## 1. 과제 개요\n\n");
    fprintf(fp, "이 과제에서는 피보나치 수열을 **반복문 방식**과 **재귀 방식**으로 구현하고, 각 방법의 수행시간을 비교하였다.  ");
    fprintf(fp, "피보나치 수열은 다음과 같이 정의한다.\n\n");
    fprintf(fp, "- F(1) = 1\n");
    fprintf(fp, "- F(2) = 1\n");
    fprintf(fp, "- F(n) = F(n-1) + F(n-2), n >= 3\n\n");

    fprintf(fp, "## 2. 사용한 방법\n\n");
    fprintf(fp, "### 2-1. 반복문 방식\n");
    fprintf(fp, "반복문 방식은 앞의 두 항을 이용하여 다음 항을 차례대로 계산하는 방법이다. 이 방법은 한 번 계산한 값을 다시 사용하기 때문에 같은 계산을 반복하지 않는다.\n\n");
    fprintf(fp, "### 2-2. 재귀 방식\n");
    fprintf(fp, "재귀 방식은 함수가 자기 자신을 다시 호출하여 피보나치 수를 계산하는 방법이다. 구현은 간단하지만 같은 값을 여러 번 계산하게 되어 비효율적이다.\n\n");

    fprintf(fp, "## 3. 실행 결과\n\n");
    fprintf(fp, "| N | 반복문 결과 | 재귀 결과 | 반복문 시간(초) | 재귀 시간(초) |\n");
    fprintf(fp, "|---|---:|---:|---:|---:|\n");

    for (n = start_n; n <= end_n; n++)
    {
        iterative_value = fibonacci_iterative(n);
        recursive_value = fibonacci_recursive(n);
        iterative_time = measure_iterative_time(n);
        recursive_time = measure_recursive_time(n);

        fprintf(fp, "| %d | %lld | %lld | %.6f | %.6f |\n",
            n, iterative_value, recursive_value, iterative_time, recursive_time);
    }

    fprintf(fp, "\n## 4. 분석\n\n");
    fprintf(fp, "실행 결과를 보면 반복문 방식은 N이 증가해도 수행시간의 변화가 크지 않다. 반면 재귀 방식은 N이 커질수록 수행시간이 빠르게 증가한다.\n\n");
    fprintf(fp, "그 이유는 반복문 방식은 필요한 계산을 한 번씩만 수행하지만, 재귀 방식은 같은 피보나치 값을 여러 번 다시 계산하기 때문이다. 예를 들어 F(6)을 구할 때 F(4), F(3), F(2) 등이 여러 번 반복 호출된다.\n\n");
    fprintf(fp, "시간 복잡도로 보면 반복문 방식은 O(n)이고, 재귀 방식은 중복 호출 때문에 훨씬 비효율적이다. 따라서 N이 커질수록 반복문 방식이 더 적합하다.\n\n");

    fprintf(fp, "## 5. 결론\n\n");
    fprintf(fp, "이번 실험을 통해 같은 피보나치 수열을 계산하더라도 구현 방법에 따라 성능 차이가 크게 발생한다는 점을 확인할 수 있었다. 반복문 방식은 효율적이고 안정적이며, 재귀 방식은 코드 구조는 단순하지만 성능 면에서는 불리하다. 따라서 큰 입력값을 처리할 때는 반복문 방식이 더 적절하다.\n");

    fclose(fp);
}

int main(void)
{
    int start_n = 1;
    int end_n = 40;

    print_result_table(start_n, end_n);
    save_markdown_report("report.md", start_n, end_n);

    printf("\nreport.md 파일이 생성되었습니다.\n");

    return 0;
}
