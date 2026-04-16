#include <stdio.h>
#include <stdlib.h>
#include "arrayList.h"

arrayList* createArrayList(int size) {
    arrayList* al;

    if (size <= 0) {
        size = 4;
    }

    al = (arrayList*)malloc(sizeof(arrayList));
    if (al == NULL) {
        printf("리스트 메모리 할당 실패\n");
        return NULL;
    }

    al->data = (elementArrayList*)malloc(sizeof(elementArrayList) * size);
    if (al->data == NULL) {
        printf("배열 메모리 할당 실패\n");
        free(al);
        return NULL;
    }

    al->size = 0;
    al->capacity = size;

    return al;
}

void destroyArrayList(arrayList* al) {
    if (al == NULL) {
        return;
    }

    free(al->data);
    free(al);
}

int isEmptyArrayList(arrayList* al) {
    if (al == NULL || al->size == 0) {
        return 1;
    }
    return 0;
}

int isFullArrayList(arrayList* al) {
    if (al != NULL && al->size == al->capacity) {
        return 1;
    }
    return 0;
}

int sizeArrayList(arrayList* al) {
    if (al == NULL) {
        return 0;
    }
    return al->size;
}

int resizeArrayList(arrayList* al) {
    elementArrayList* temp;
    int newCapacity;

    if (al == NULL) {
        return 0;
    }

    newCapacity = al->capacity * 2;
    if (newCapacity <= 0) {
        newCapacity = 4;
    }

    temp = (elementArrayList*)realloc(al->data, sizeof(elementArrayList) * newCapacity);
    if (temp == NULL) {
        printf("realloc 실패: 배열 크기 확장 불가\n");
        return 0;
    }

    al->data = temp;
    al->capacity = newCapacity;

    printf("배열 크기 확장 완료 -> 새로운 capacity: %d\n", al->capacity);
    return 1;
}

int insertArrayList(arrayList* al, int pos, elementArrayList item) {
    int i;

    if (al == NULL) {
        return 0;
    }

    if (pos < 0 || pos > al->size) {
        return 0;
    }

    /* 포화 상태이면 자동 확장 */
    if (isFullArrayList(al)) {
        if (!resizeArrayList(al)) {
            return 0;
        }
    }

    for (i = al->size - 1; i >= pos; i--) {
        al->data[i + 1] = al->data[i];
    }

    al->data[pos] = item;
    al->size++;

    return 1;
}

elementArrayList deleteArrayList(arrayList* al, int pos) {
    int i;
    elementArrayList item;

    if (al == NULL) {
        return -1;
    }

    if (pos < 0 || pos > al->size - 1) {
        return -1;
    }

    item = al->data[pos];

    for (i = pos; i < al->size - 1; i++) {
        al->data[i] = al->data[i + 1];
    }

    al->size--;

    return item;
}

int initArrayList(arrayList* al) {
    if (al == NULL) {
        return 0;
    }

    al->size = 0;
    return 1;
}

elementArrayList getItemArrayList(arrayList* al, int pos) {
    if (al == NULL) {
        return -1;
    }

    if (pos < 0 || pos > al->size - 1) {
        return -1;
    }

    return al->data[pos];
}

int replaceItemArrayList(arrayList* al, int pos, elementArrayList item) {
    if (al == NULL) {
        return 0;
    }

    if (pos < 0 || pos > al->size - 1) {
        return 0;
    }

    al->data[pos] = item;
    return 1;
}

void printArrayList(arrayList* al) {
    int i;

    if (al == NULL) {
        printf("리스트가 존재하지 않습니다.\n");
        return;
    }

    printf("순차 리스트: ");
    for (i = 0; i < al->size; i++) {
        printf("%d ", al->data[i]);
    }
    printf("\n");

    printf("현재 size = %d, capacity = %d\n", al->size, al->capacity);
}