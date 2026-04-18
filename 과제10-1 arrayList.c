#include <stdio.h>
#include <stdlib.h>
#include "arrayList.h"

arrayList* createArrayList(int size) {
    arrayList* al;

    al = (arrayList*)malloc(sizeof(arrayList));
    if (al == NULL) return NULL;

    al->data = (element*)malloc(sizeof(element) * size);
    if (al->data == NULL) {
        free(al);
        return NULL;
    }

    al->size = 0;
    al->capacity = size;

    return al;
}

void destroyArrayList(arrayList* al) {
    if (al != NULL) {
        free(al->data);
        free(al);
    }
}

int isEmptyArrayList(arrayList* al) {
    return (al->size == 0);
}

int isFullArrayList(arrayList* al) {
    return (al->size == al->capacity);
}

int sizeArrayList(arrayList* al) {
    return al->size;
}

int insertArrayList(arrayList* al, int pos, element item) {
    int i;
    element* newData;

    if (al == NULL) return 0;
    if (item <= 0) return 0;
    if (pos < 0 || pos > al->size) return 0;

    if (isFullArrayList(al)) {
        newData = (element*)realloc(al->data, sizeof(element) * (al->capacity * 2));
        if (newData == NULL) return 0;
        al->data = newData;
        al->capacity = al->capacity * 2;
    }

    for (i = al->size - 1; i >= pos; i--) {
        al->data[i + 1] = al->data[i];
    }

    al->data[pos] = item;
    al->size++;

    return 1;
}

element deleteArrayList(arrayList* al, int pos) {
    int i;
    element item;

    if (al == NULL) return -1;
    if (isEmptyArrayList(al)) return -1;
    if (pos < 0 || pos >= al->size) return -1;

    item = al->data[pos];

    for (i = pos; i < al->size - 1; i++) {
        al->data[i] = al->data[i + 1];
    }

    al->size--;

    return item;
}

element getItemArrayList(arrayList* al, int pos) {
    if (al == NULL) return -1;
    if (pos < 0 || pos >= al->size) return -1;

    return al->data[pos];
}

int replaceItemArrayList(arrayList* al, int pos, element item) {
    if (al == NULL) return 0;
    if (item <= 0) return 0;
    if (pos < 0 || pos >= al->size) return 0;

    al->data[pos] = item;
    return 1;
}

int clearArrayList(arrayList* al) {
    if (al == NULL) return 0;

    al->size = 0;
    return 1;
}

void printArrayList(arrayList* al) {
    int i;

    if (al == NULL) return;

    if (isEmptyArrayList(al)) {
        printf("리스트가 비어 있습니다.\n");
        return;
    }

    printf("리스트 내용: ");
    for (i = 0; i < al->size; i++) {
        printf("%d ", al->data[i]);
    }
    printf("\n");
}