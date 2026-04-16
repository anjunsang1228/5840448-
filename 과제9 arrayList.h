#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef int elementArrayList;

typedef struct arrayListType {
    elementArrayList* data;
    int size;
    int capacity;
} arrayList;

arrayList* createArrayList(int size);
void destroyArrayList(arrayList* al);
int isEmptyArrayList(arrayList* al);
int isFullArrayList(arrayList* al);
int sizeArrayList(arrayList* al);

/* 배열이 가득 찼을 때 크기를 늘리는 함수 */
int resizeArrayList(arrayList* al);

int insertArrayList(arrayList* al, int pos, elementArrayList item);
elementArrayList deleteArrayList(arrayList* al, int pos);
int initArrayList(arrayList* al);
elementArrayList getItemArrayList(arrayList* al, int pos);
int replaceItemArrayList(arrayList* al, int pos, elementArrayList item);
void printArrayList(arrayList* al);

#endif