#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NAME_LEN 50

typedef struct {
    char name[NAME_LEN];
    int id;
    int score;
} Student;


void trim_newline(char str[]) {
    int len = (int)strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}


int count_names(const char* filename) {
    FILE* fp = fopen(filename, "r");
    char buffer[NAME_LEN];
    int count = 0;

    if (fp == NULL) {
        return -1;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        count++;
    }

    fclose(fp);
    return count;
}


int load_students(const char* filename, Student arr[], int n) {
    FILE* fp = fopen(filename, "r");
    int i;

    if (fp == NULL) {
        return 0;
    }

    for (i = 0; i < n; i++) {
        if (fgets(arr[i].name, sizeof(arr[i].name), fp) == NULL) {
            fclose(fp);
            return 0;
        }

        trim_newline(arr[i].name);
        arr[i].id = i + 1;
        arr[i].score = rand() % 100 + 1;
    }

    fclose(fp);
    return 1;
}


void print_students(Student arr[], int n) {
    int i;

    printf("===== 학생 정보 =====\n");
    for (i = 0; i < n; i++) {
        printf("%d번 학생 -> 이름: %-10s 학번: %d 성적: %d\n",
            i + 1, arr[i].name, arr[i].id, arr[i].score);
    }
}


int get_min_index(Student arr[], int n) {
    int i;
    int min_index = 0;

    for (i = 1; i < n; i++) {
        if (arr[i].score < arr[min_index].score) {
            min_index = i;
        }
    }

    return min_index;
}


int get_max_index(Student arr[], int n) {
    int i;
    int max_index = 0;

    for (i = 1; i < n; i++) {
        if (arr[i].score > arr[max_index].score) {
            max_index = i;
        }
    }

    return max_index;
}


double get_average(Student arr[], int n) {
    int i;
    int sum = 0;

    for (i = 0; i < n; i++) {
        sum += arr[i].score;
    }

    return (double)sum / n;
}

int main(void) {
    const char* filename = "name_list.txt";
    Student* students = NULL;
    int n;
    int min_index, max_index;
    double average;

    srand((unsigned int)time(NULL));

    n = count_names(filename);
    if (n <= 0) {
        printf("파일을 열 수 없거나 이름이 존재하지 않습니다.\n");
        return 1;
    }

    students = (Student*)malloc(sizeof(Student) * n);
    if (students == NULL) {
        printf("동적 메모리 할당에 실패했습니다.\n");
        return 1;
    }

    if (!load_students(filename, students, n)) {
        printf("학생 정보를 불러오는 데 실패했습니다.\n");
        free(students);
        return 1;
    }

    print_students(students, n);

    min_index = get_min_index(students, n);
    max_index = get_max_index(students, n);
    average = get_average(students, n);

    printf("\n===== 결과 =====\n");
    printf("최저점 학생 정보\n");
    printf("이름: %s, 학번: %d, 성적: %d\n",
        students[min_index].name,
        students[min_index].id,
        students[min_index].score);

    printf("\n최고점 학생 정보\n");
    printf("이름: %s, 학번: %d, 성적: %d\n",
        students[max_index].name,
        students[max_index].id,
        students[max_index].score);

    printf("\n평균 점수: %.2f\n", average);

    free(students);
    return 0;
}