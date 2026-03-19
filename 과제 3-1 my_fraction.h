#ifndef MY_FRACTION_H
#define MY_FRACTION_H

typedef struct {
    int numerator;   
    int denominator; 
} Fraction;

Fraction createFraction(int n, int d);
Fraction reduce(Fraction f);
Fraction add(Fraction f1, Fraction f2);
void printFraction(Fraction f);

#endif
