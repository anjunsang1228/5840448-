#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "polyList.h"

#define DEFAULT_CAPACITY 10

/* 내부에서만 사용하는 함수: 순차 리스트 공간이 부족하면 2배로 늘린다. */
static int ensureCapacity(Polynomial* poly, int minCapacity) {
    PolyTerm* newData;
    int newCapacity;

    if (poly == NULL) {
        return 0;
    }

    if (poly->capacity >= minCapacity) {
        return 1;
    }

    newCapacity = poly->capacity;
    if (newCapacity <= 0) {
        newCapacity = DEFAULT_CAPACITY;
    }

    while (newCapacity < minCapacity) {
        newCapacity *= 2;
    }

    newData = (PolyTerm*)realloc(poly->data, sizeof(PolyTerm) * newCapacity);
    if (newData == NULL) {
        return 0;
    }

    poly->data = newData;
    poly->capacity = newCapacity;
    return 1;
}

/* qsort용 비교 함수: 지수가 큰 항이 앞에 오도록 정렬 */
static int compareTermByExpDesc(const void* left, const void* right) {
    const PolyTerm* a = (const PolyTerm*)left;
    const PolyTerm* b = (const PolyTerm*)right;

    return b->exp - a->exp;
}

Polynomial* createPolynomial(int capacity) {
    Polynomial* poly;

    if (capacity <= 0) {
        capacity = DEFAULT_CAPACITY;
    }

    poly = (Polynomial*)malloc(sizeof(Polynomial));
    if (poly == NULL) {
        return NULL;
    }

    poly->data = (PolyTerm*)malloc(sizeof(PolyTerm) * capacity);
    if (poly->data == NULL) {
        free(poly);
        return NULL;
    }

    poly->size = 0;
    poly->capacity = capacity;
    return poly;
}

void destroyPolynomial(Polynomial* poly) {
    if (poly != NULL) {
        free(poly->data);
        free(poly);
    }
}

void clearPolynomial(Polynomial* poly) {
    if (poly != NULL) {
        poly->size = 0;
    }
}

int isEmptyPolynomial(const Polynomial* poly) {
    return (poly == NULL || poly->size == 0);
}

int appendTerm(Polynomial* poly, int coef, int exp) {
    if (poly == NULL || exp < 0) {
        return 0;
    }

    /* 계수가 0인 항은 결과에 영향을 주지 않으므로 저장하지 않는다. */
    if (coef == 0) {
        return 1;
    }

    if (!ensureCapacity(poly, poly->size + 1)) {
        return 0;
    }

    poly->data[poly->size].coef = coef;
    poly->data[poly->size].exp = exp;
    poly->size++;

    return 1;
}

void sortPolynomial(Polynomial* poly) {
    if (poly != NULL && poly->size > 1) {
        qsort(poly->data, poly->size, sizeof(PolyTerm), compareTermByExpDesc);
    }
}

void combineLikeTerms(Polynomial* poly) {
    int i;
    int writeIndex;
    int currentCoef;
    int currentExp;

    if (poly == NULL || poly->size == 0) {
        return;
    }

    sortPolynomial(poly);

    writeIndex = 0;
    currentCoef = poly->data[0].coef;
    currentExp = poly->data[0].exp;

    for (i = 1; i < poly->size; i++) {
        if (poly->data[i].exp == currentExp) {
            currentCoef += poly->data[i].coef;
        }
        else {
            if (currentCoef != 0) {
                poly->data[writeIndex].coef = currentCoef;
                poly->data[writeIndex].exp = currentExp;
                writeIndex++;
            }
            currentCoef = poly->data[i].coef;
            currentExp = poly->data[i].exp;
        }
    }

    if (currentCoef != 0) {
        poly->data[writeIndex].coef = currentCoef;
        poly->data[writeIndex].exp = currentExp;
        writeIndex++;
    }

    poly->size = writeIndex;
}

/*
    입력 예: 3X^2+2X^1+1X^0
    공백은 무시하며, x와 X를 모두 허용한다.
*/
int parsePolynomial(Polynomial* poly, const char* input) {
    char* cleanInput;
    char* token;
    int i;
    int j;
    int length;
    int parsedCount;

    if (poly == NULL || input == NULL) {
        return 0;
    }

    clearPolynomial(poly);
    length = (int)strlen(input);
    cleanInput = (char*)malloc(length + 1);
    if (cleanInput == NULL) {
        return 0;
    }

    j = 0;
    for (i = 0; i < length; i++) {
        if (!isspace((unsigned char)input[i])) {
            cleanInput[j] = input[i];
            j++;
        }
    }
    cleanInput[j] = '\0';

    parsedCount = 0;
    token = strtok(cleanInput, "+");

    while (token != NULL) {
        int coef;
        int exp;
        char xChar;
        char hatChar;

        if (sscanf(token, "%d%c%c%d", &coef, &xChar, &hatChar, &exp) != 4) {
            free(cleanInput);
            clearPolynomial(poly);
            return 0;
        }

        if ((xChar != 'X' && xChar != 'x') || hatChar != '^' || exp < 0) {
            free(cleanInput);
            clearPolynomial(poly);
            return 0;
        }

        if (!appendTerm(poly, coef, exp)) {
            free(cleanInput);
            clearPolynomial(poly);
            return 0;
        }

        parsedCount++;
        token = strtok(NULL, "+");
    }

    free(cleanInput);

    if (parsedCount == 0) {
        return 0;
    }

    combineLikeTerms(poly);
    return 1;
}

/*
    수정된 다항식 덧셈 코드
    핵심: 한쪽 다항식의 항이 먼저 끝나도, 남은 항을 모두 결과에 복사해야 한다.
*/
Polynomial* addPolynomial(const Polynomial* a, const Polynomial* b) {
    Polynomial* result;
    int i;
    int j;

    if (a == NULL || b == NULL) {
        return NULL;
    }

    result = createPolynomial(a->size + b->size + DEFAULT_CAPACITY);
    if (result == NULL) {
        return NULL;
    }

    i = 0;
    j = 0;

    while (i < a->size && j < b->size) {
        if (a->data[i].exp > b->data[j].exp) {
            appendTerm(result, a->data[i].coef, a->data[i].exp);
            i++;
        }
        else if (a->data[i].exp < b->data[j].exp) {
            appendTerm(result, b->data[j].coef, b->data[j].exp);
            j++;
        }
        else {
            appendTerm(result, a->data[i].coef + b->data[j].coef, a->data[i].exp);
            i++;
            j++;
        }
    }

    while (i < a->size) {
        appendTerm(result, a->data[i].coef, a->data[i].exp);
        i++;
    }

    while (j < b->size) {
        appendTerm(result, b->data[j].coef, b->data[j].exp);
        j++;
    }

    combineLikeTerms(result);
    return result;
}

Polynomial* multiplyPolynomial(const Polynomial* a, const Polynomial* b) {
    Polynomial* result;
    int i;
    int j;

    if (a == NULL || b == NULL) {
        return NULL;
    }

    result = createPolynomial(a->size * b->size + DEFAULT_CAPACITY);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < a->size; i++) {
        for (j = 0; j < b->size; j++) {
            int newCoef = a->data[i].coef * b->data[j].coef;
            int newExp = a->data[i].exp + b->data[j].exp;
            appendTerm(result, newCoef, newExp);
        }
    }

    combineLikeTerms(result);
    return result;
}

void printPolynomial(const Polynomial* poly) {
    int i;

    if (poly == NULL || poly->size == 0) {
        printf("0X^0");
        return;
    }

    for (i = 0; i < poly->size; i++) {
        int coef = poly->data[i].coef;
        int exp = poly->data[i].exp;

        if (i > 0 && coef > 0) {
            printf("+");
        }

        printf("%dX^%d", coef, exp);
    }
}
