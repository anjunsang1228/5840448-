#include <stdio.h>

#define N 3

int main(void) {
    int magic[N][N];
    int i, j;
    int num = 1;
    int row = 0;
    int col = N / 2;
    int newRow, newCol;
    int sum;

    if (N % 2 == 0) {
        printf("N은 홀수여야 합니다.\n");
        return 1;
    }

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            magic[i][j] = 0;
        }
    }

    while (num <= N * N) {
        magic[row][col] = num;

        newRow = row - 1;
        newCol = col + 1;

        if (newRow < 0) {
            newRow = N - 1;
        }

        if (newCol >= N) {
            newCol = 0;
        }

        if (magic[newRow][newCol] != 0) {
            row = row + 1;
            if (row >= N) {
                row = 0;
            }
        }
        else {
            row = newRow;
            col = newCol;
        }

        num++;
    }

    printf("홀수 마방진 (%d x %d)\n\n", N, N);

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%4d", magic[i][j]);
        }
        printf("\n");
    }

    printf("\n가로 합\n");
    for (i = 0; i < N; i++) {
        sum = 0;
        for (j = 0; j < N; j++) {
            sum += magic[i][j];
        }
        printf("%d행 합 = %d\n", i + 1, sum);
    }

    printf("\n세로 합\n");
    for (j = 0; j < N; j++) {
        sum = 0;
        for (i = 0; i < N; i++) {
            sum += magic[i][j];
        }
        printf("%d열 합 = %d\n", j + 1, sum);
    }

    printf("\n대각선 합\n");

    sum = 0;
    for (i = 0; i < N; i++) {
        sum += magic[i][i];
    }
    printf("왼쪽 위 -> 오른쪽 아래 대각선 합 = %d\n", sum);

    sum = 0;
    for (i = 0; i < N; i++) {
        sum += magic[i][N - 1 - i];
    }
    printf("오른쪽 위 -> 왼쪽 아래 대각선 합 = %d\n", sum);

    return 0;
}