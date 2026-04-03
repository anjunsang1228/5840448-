#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int N;
    int* arr;
    int i;
    int sum = 0;
    int max, min;

    printf("배열의 크기 N을 입력하세요: ");
    scanf("%d", &N);

    if (N <= 0) {
        printf("N은 1 이상의 정수여야 합니다.\n");
        return 1;
    }

    arr = (int*)malloc(sizeof(int) * N);

    if (arr == NULL) {
        printf("메모리 할당에 실패했습니다.\n");
        return 1;
    }

    srand((unsigned int)time(NULL));

    for (i = 0; i < N; i++) {
        *(arr + i) = rand() % (N + 1);
    }

    printf("\n배열을 처음부터 끝까지 출력:\n");
    for (i = 0; i < N; i++) {
        printf("%d ", *(arr + i));
    }
    printf("\n");

    printf("\n배열을 뒤에서부터 처음까지 출력:\n");
    for (i = N - 1; i >= 0; i--) {
        printf("%d ", *(arr + i));
    }
    printf("\n");

    max = *arr;
    min = *arr;

    for (i = 0; i < N; i++) {
        sum += *(arr + i);

        if (*(arr + i) > max) {
            max = *(arr + i);
        }

        if (*(arr + i) < min) {
            min = *(arr + i);
        }
    }

    printf("\n배열 전체의 총합: %d\n", sum);
    printf("배열의 최대값: %d\n", max);
    printf("배열의 최소값: %d\n", min);

    free(arr);

    return 0;
}