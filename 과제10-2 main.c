#include <stdio.h>
#include "sparseMatrix.h"

int main() {
    sparseMatrix* a;
    sparseMatrix* b;
    int moveCount;

    a = createSparseMatrix(10, 10, 20);
    b = createSparseMatrix(10, 10, 20);

    if (a == NULL || b == NULL) {
        printf("희소행렬 생성 실패\n");
        return 1;
    }

    initSparseMatrix(a);

    printf("원본 행렬\n");
    printNormalMatrix(a);

    printf("\n원본 희소행렬\n");
    printSparseMatrix(a);

    transposeSparseMatrix(a, b, &moveCount);

    printf("\n전치 희소행렬\n");
    printSparseMatrix(b);

    printf("\n전치 행렬\n");
    printNormalMatrix(b);

    printf("\n데이터 이동 횟수: %d\n", moveCount);

    destroySparseMatrix(a);
    destroySparseMatrix(b);

    return 0;
}