#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "polyList.h"

#define MAX_INPUT_LENGTH 1000

int main(void) {
    char inputA[MAX_INPUT_LENGTH];
    char inputB[MAX_INPUT_LENGTH];

    Polynomial* polyA = createPolynomial(10);
    Polynomial* polyB = createPolynomial(10);
    Polynomial* sum = NULL;
    Polynomial* product = NULL;

    if (polyA == NULL || polyB == NULL) {
        printf("메모리 할당에 실패했습니다.\n");
        destroyPolynomial(polyA);
        destroyPolynomial(polyB);
        return 1;
    }

    printf("첫 번째 다항식을 입력하세요.\n");
    printf("입력 예: 3X^2+2X^1+1X^0\n");
    printf("A(x) = ");

    if (fgets(inputA, sizeof(inputA), stdin) == NULL) {
        printf("입력 오류가 발생했습니다.\n");
        destroyPolynomial(polyA);
        destroyPolynomial(polyB);
        return 1;
    }

    printf("\n두 번째 다항식을 입력하세요.\n");
    printf("입력 예: 2X^1+1X^0\n");
    printf("B(x) = ");

    if (fgets(inputB, sizeof(inputB), stdin) == NULL) {
        printf("입력 오류가 발생했습니다.\n");
        destroyPolynomial(polyA);
        destroyPolynomial(polyB);
        return 1;
    }

    if (!parsePolynomial(polyA, inputA)) {
        printf("첫 번째 다항식 입력 형식이 올바르지 않습니다.\n");
        printf("예시처럼 3X^2+2X^1+1X^0 형식으로 입력하세요.\n");
        destroyPolynomial(polyA);
        destroyPolynomial(polyB);
        return 1;
    }

    if (!parsePolynomial(polyB, inputB)) {
        printf("두 번째 다항식 입력 형식이 올바르지 않습니다.\n");
        printf("예시처럼 3X^2+2X^1+1X^0 형식으로 입력하세요.\n");
        destroyPolynomial(polyA);
        destroyPolynomial(polyB);
        return 1;
    }

    sum = addPolynomial(polyA, polyB);
    product = multiplyPolynomial(polyA, polyB);

    if (sum == NULL || product == NULL) {
        printf("다항식 연산 중 메모리 할당에 실패했습니다.\n");
        destroyPolynomial(polyA);
        destroyPolynomial(polyB);
        destroyPolynomial(sum);
        destroyPolynomial(product);
        return 1;
    }

    printf("\n========== 연산 결과 ==========\n");

    printf("A(x) = ");
    printPolynomial(polyA);
    printf("\n");

    printf("B(x) = ");
    printPolynomial(polyB);
    printf("\n");

    printf("A(x) + B(x) = ");
    printPolynomial(sum);
    printf("\n");

    printf("A(x) * B(x) = ");
    printPolynomial(product);
    printf("\n");

    destroyPolynomial(polyA);
    destroyPolynomial(polyB);
    destroyPolynomial(sum);
    destroyPolynomial(product);

    return 0;
}
