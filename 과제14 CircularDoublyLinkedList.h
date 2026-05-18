#ifndef CIRCULAR_DOUBLY_LINKED_LIST_H
#define CIRCULAR_DOUBLY_LINKED_LIST_H

#include <stdbool.h>

typedef int ElementType;

typedef struct Node {
    ElementType data;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct CircularDoublyLinkedList {
    Node* head;
    int size;
} CDList;

CDList* createList();
void destroyList(CDList* list);
bool isEmpty(CDList* list);
int getSize(CDList* list);

bool insertFirst(CDList* list, ElementType item);
bool insertLast(CDList* list, ElementType item);
bool insertAt(CDList* list, int index, ElementType item);

bool deleteAt(CDList* list, int index, ElementType* pDeletedItem);

void printList(CDList* list);

#endif