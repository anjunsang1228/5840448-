#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include "arrayList.h"

typedef struct {
    int row;
    int col;
    int value;
} matrixTerm;

typedef struct {
    int rows;
    int cols;
    int terms;
    matrixTerm* data;
} sparseMatrix;

sparseMatrix* createSparseMatrix(int rows, int cols, int terms);
void destroySparseMatrix(sparseMatrix* sm);
void initSparseMatrix(sparseMatrix* sm);
void printSparseMatrix(sparseMatrix* sm);
void printNormalMatrix(sparseMatrix* sm);
void transposeSparseMatrix(sparseMatrix* a, sparseMatrix* b, int* moveCount);

#endif
