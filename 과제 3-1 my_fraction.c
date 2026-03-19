#include <stdio.h>
#include "my_fraction.h"

static int get_gcd(int a, int b) {
    if (b == 0) return a;
    return get_gcd(b, a % b);
}

Fraction reduce(Fraction f) {
    if (f.denominator == 0) return f; 

    int common = get_gcd(f.numerator, f.denominator);
    f.numerator /= common;
    f.denominator /= common;

   
    if (f.denominator < 0) {
        f.numerator = -f.numerator;
        f.denominator = -f.denominator;
    }
    return f;
}


Fraction createFraction(int n, int d) {
    Fraction f = { n, d };
    return reduce(f);
}


Fraction add(Fraction f1, Fraction f2) {
    Fraction result;
    result.numerator = (f1.numerator * f2.denominator) + (f2.numerator * f1.denominator);
    result.denominator = f1.denominator * f2.denominator;
    return reduce(result);
}


void printFraction(Fraction f) {
    printf("%d/%d", f.numerator, f.denominator);
}
