#include "fibonacci.h"


long long fibonacci_iterative(int n) {
    long long prev = 1, curr = 1, next;
    int i;

    if (n == 1 || n == 2) {
        return 1;
    }

    for (i = 3; i <= n; i++) {
        next = prev + curr;
        prev = curr;
        curr = next;
    }

    return curr;
}


long long fibonacci_recursive(int n) {
    if (n == 1 || n == 2) {
        return 1;
    }

    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}