#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int N;
    int** arr;
    int i, j;
    int num;
    int row, col;
    int nextRow, nextCol;
    int sum;

    printf("홀수 N을 입력하세요: ");
    if (scanf_s("%d", &N) != 1) {
        printf("입력이 잘못되었습니다.\n");
        return 1;
    }

    if (N <= 0 || N % 2 == 0) {
        printf("N은 1 이상의 홀수여야 합니다.\n");
        return 1;
    }

    arr = (int**)malloc(sizeof(int*) * N);
    if (arr == NULL) {
        printf("메모리 할당 실패\n");
        return 1;
    }

    for (i = 0; i < N; i++) {
        *(arr + i) = (int*)malloc(sizeof(int) * N);
        if (*(arr + i) == NULL) {
            printf("메모리 할당 실패\n");
            return 1;
        }
    }

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            *(*(arr + i) + j) = 0;
        }
    }

    row = 0;
    col = N / 2;

    for (num = 1; num <= N * N; num++) {
        *(*(arr + row) + col) = num;

        nextRow = row - 1;
        nextCol = col + 1;

        if (nextRow < 0) {
            nextRow = N - 1;
        }
        if (nextCol >= N) {
            nextCol = 0;
        }

        if (*(*(arr + nextRow) + nextCol) != 0) {
            row = row + 1;
            if (row >= N) {
                row = 0;
            }
        }
        else {
            row = nextRow;
            col = nextCol;
        }
    }

    printf("\n마방진 출력\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%4d", *(*(arr + i) + j));
        }
        printf("\n");
    }

    printf("\n가로 합\n");
    for (i = 0; i < N; i++) {
        sum = 0;
        for (j = 0; j < N; j++) {
            sum += *(*(arr + i) + j);
        }
        printf("%d번째 가로 합: %d\n", i + 1, sum);
    }

    printf("\n세로 합\n");
    for (j = 0; j < N; j++) {
        sum = 0;
        for (i = 0; i < N; i++) {
            sum += *(*(arr + i) + j);
        }
        printf("%d번째 세로 합: %d\n", j + 1, sum);
    }

    printf("\n대각선 합\n");

    sum = 0;
    for (i = 0; i < N; i++) {
        sum += *(*(arr + i) + i);
    }
    printf("왼쪽 위 -> 오른쪽 아래 대각선 합: %d\n", sum);

    sum = 0;
    for (i = 0; i < N; i++) {
        sum += *(*(arr + i) + (N - 1 - i));
    }
    printf("오른쪽 위 -> 왼쪽 아래 대각선 합: %d\n", sum);

    for (i = 0; i < N; i++) {
        free(*(arr + i));
    }
    free(arr);

    return 0;
}