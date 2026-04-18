#include <stdio.h>
#include <stdlib.h>
#include "sparseMatrix.h"

sparseMatrix* createSparseMatrix(int rows, int cols, int terms) {
    sparseMatrix* sm;

    sm = (sparseMatrix*)malloc(sizeof(sparseMatrix));
    if (sm == NULL) return NULL;

    sm->data = (matrixTerm*)malloc(sizeof(matrixTerm) * terms);
    if (sm->data == NULL) {
        free(sm);
        return NULL;
    }

    sm->rows = rows;
    sm->cols = cols;
    sm->terms = terms;

    return sm;
}

void destroySparseMatrix(sparseMatrix* sm) {
    if (sm != NULL) {
        free(sm->data);
        free(sm);
    }
}

void initSparseMatrix(sparseMatrix* sm) {
    int sample[20][3] = {
        {0, 1, 5}, {0, 4, 3}, {0, 7, 8},
        {1, 0, 2}, {1, 5, 7}, {1, 9, 6},
        {2, 2, 4}, {2, 8, 1},
        {3, 3, 9}, {3, 6, 2},
        {4, 1, 8}, {4, 7, 5},
        {5, 0, 3}, {5, 5, 6},
        {6, 2, 7}, {6, 9, 4},
        {7, 4, 2}, {8, 6, 1},
        {9, 3, 5}, {9, 8, 9}
    };

    int i;

    for (i = 0; i < 20; i++) {
        sm->data[i].row = sample[i][0];
        sm->data[i].col = sample[i][1];
        sm->data[i].value = sample[i][2];
    }
}

void printSparseMatrix(sparseMatrix* sm) {
    int i;

    printf("\n희소행렬 표현\n");
    printf("row col value\n");

    for (i = 0; i < sm->terms; i++) {
        printf("%3d %3d %3d\n",
            sm->data[i].row,
            sm->data[i].col,
            sm->data[i].value);
    }
}

void printNormalMatrix(sparseMatrix* sm) {
    int arr[10][10] = { 0 };
    int i, j;

    for (i = 0; i < sm->terms; i++) {
        arr[sm->data[i].row][sm->data[i].col] = sm->data[i].value;
    }

    printf("\n일반 행렬 형태\n");
    for (i = 0; i < sm->rows; i++) {
        for (j = 0; j < sm->cols; j++) {
            printf("%3d ", arr[i][j]);
        }
        printf("\n");
    }
}

void transposeSparseMatrix(sparseMatrix* a, sparseMatrix* b, int* moveCount) {
    int i, j, k = 0;

    b->rows = a->cols;
    b->cols = a->rows;
    b->terms = a->terms;
    *moveCount = 0;

    for (i = 0; i < a->cols; i++) {
        for (j = 0; j < a->terms; j++) {
            if (a->data[j].col == i) {
                b->data[k].row = a->data[j].col;
                b->data[k].col = a->data[j].row;
                b->data[k].value = a->data[j].value;
                k++;
                (*moveCount)++;
            }
        }
    }
}