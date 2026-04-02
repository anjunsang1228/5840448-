#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

int main(void) {
    int arr[N];
    int i;
    int sum = 0;
    int max, min;

    srand((unsigned int)time(NULL));

    for (i = 0; i < N; i++) {
        arr[i] = rand() % (N + 1);
    }

    printf("배열을 처음부터 끝까지 출력:\n");
    for (i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    printf("배열을 뒤에서부터 처음까지 출력:\n");
    for (i = N - 1; i >= 0; i--) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    max = arr[0];
    min = arr[0];

    for (i = 0; i < N; i++) {
        sum += arr[i];

        if (arr[i] > max) {
            max = arr[i];
        }

        if (arr[i] < min) {
            min = arr[i];
        }
    }

    printf("배열 전체의 총합: %d\n", sum);
    printf("배열의 최대값: %d\n", max);
    printf("배열의 최소값: %d\n", min);

    return 0;
}