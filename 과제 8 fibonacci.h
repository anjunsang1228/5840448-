#ifndef FIBONACCI_H
#define FIBONACCI_H

long long fibonacci_iterative(int n);
long long fibonacci_recursive(int n);
double measure_iterative_time(int n);
double measure_recursive_time(int n);
void print_result_table(int start, int end);
void save_markdown_report(const char* filename, int start, int end);

#endif

