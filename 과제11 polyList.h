#ifndef POLY_LIST_H
#define POLY_LIST_H

/*
    순차 리스트를 이용한 다항식 저장 구조
    - 하나의 항: 계수(coef), 지수(exp)
    - 하나의 다항식: 항 배열(data), 현재 항 개수(size), 최대 저장 개수(capacity)
*/

typedef struct {
    int coef;   // 계수
    int exp;    // 지수
} PolyTerm;

typedef struct {
    PolyTerm* data; // 항을 저장하는 순차 리스트 배열
    int size;       // 현재 저장된 항의 개수
    int capacity;   // 배열의 최대 저장 공간
} Polynomial;

Polynomial* createPolynomial(int capacity);
void destroyPolynomial(Polynomial* poly);
void clearPolynomial(Polynomial* poly);

int isEmptyPolynomial(const Polynomial* poly);
int appendTerm(Polynomial* poly, int coef, int exp);
int parsePolynomial(Polynomial* poly, const char* input);

void sortPolynomial(Polynomial* poly);
void combineLikeTerms(Polynomial* poly);

Polynomial* addPolynomial(const Polynomial* a, const Polynomial* b);
Polynomial* multiplyPolynomial(const Polynomial* a, const Polynomial* b);

void printPolynomial(const Polynomial* poly);

#endif
