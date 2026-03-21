#ifdef _WIN32
/* MSVC가 “unsafe” 경고를 내지 않게 해줍니다. */
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------- 1) 분수 타입 & 기본 유틸 ---------- */
typedef struct { long long n, d; } Fraction;   /* n = numerator, d = denominator */

/* 최대공약수 – 유클리드 호제법 */
static long long gcd_ll(long long a, long long b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b) { long long t = b; b = a % b; a = t; }
    return a ? a : 1;                 /* a==0이면 1 반환 (0/0 은 사용되지 않음) */
}

/* 약분 + 정규화 (분모는 양수) */
static Fraction norm(Fraction f) {
    if (f.d == 0) {
        fprintf(stderr, "Error: denominator cannot be zero.\n");
        exit(EXIT_FAILURE);
    }
    if (f.d < 0) { f.n = -f.n; f.d = -f.d; }
    long long g = gcd_ll(f.n, f.d);
    f.n /= g; f.d /= g;
    return f;
}

/* 문자열 "A/B" → Fraction (예: "3/7") */
static Fraction parse_frac(const char* s) {
    const char* slash = strchr(s, '/');
    if (!slash) {
        fprintf(stderr, "Invalid fraction format: %s (expected A/B)\n", s);
        exit(EXIT_FAILURE);
    }
    char numbuf[32] = { 0 }, denbuf[32] = { 0 };
    size_t nlen = slash - s;
    strncpy(numbuf, s, nlen);
    strcpy(denbuf, slash + 1);
    return norm((Fraction) { atoll(numbuf), atoll(denbuf) });
}

/* 사칙연산 – 결과는 자동 약분 */
static Fraction add(Fraction a, Fraction b) {
    return norm((Fraction) { a.n* b.d + b.n * a.d, a.d* b.d });
}
static Fraction mul(Fraction a, Fraction b) {
    return norm((Fraction) { a.n* b.n, a.d* b.d });
}

/* ---------- 2) 사각형 연산 ---------- */
static Fraction rectangle_perimeter(Fraction w, Fraction h) {
    Fraction sum = add(w, h);
    Fraction two = { 2, 1 };
    return mul(two, sum);                 /* 2·(w+h) */
}
static Fraction rectangle_area(Fraction w, Fraction h) {
    return mul(w, h);                     /* w·h */
}

/* ---------- 3) main ---------- */
int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr,
            "Usage: %s <width A/B> <height C/D>\n"
            "Example: %s 3/7 4/9\n",
            argv[0], argv[0]);
        return EXIT_FAILURE;
    }

    Fraction width = parse_frac(argv[1]);
    Fraction height = parse_frac(argv[2]);

    Fraction per = rectangle_perimeter(width, height);
    Fraction area = rectangle_area(width, height);

    /* %lld 은 C99 표준이며 MSVC(Visual Studio 2015 이후)에서도 지원합니다. */
    printf("Perimeter: %lld/%lld, Area: %lld/%lld\n",
        per.n, per.d, area.n, area.d);
    return EXIT_SUCCESS;
}