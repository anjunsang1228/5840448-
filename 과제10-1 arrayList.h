#ifndef ARRAYLIST_H
#define ARRAYLIST_H

typedef int element;

typedef struct arrayListType {
    element* data;
    int size;
    int capacity;
} arrayList;

arrayList* createArrayList(int size);
void destroyArrayList(arrayList* al);
int isEmptyArrayList(arrayList* al);
int isFullArrayList(arrayList* al);
int sizeArrayList(arrayList* al);
int insertArrayList(arrayList* al, int pos, element item);
element deleteArrayList(arrayList* al, int pos);
element getItemArrayList(arrayList* al, int pos);
int replaceItemArrayList(arrayList* al, int pos, element item);
int clearArrayList(arrayList* al);
void printArrayList(arrayList* al);

#endif