#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 노드 구조체 정의
typedef struct ListNode {
    int data;
    struct ListNode* next;
} ListNode;

// 연결 리스트 관리 구조체
typedef struct LinkedList {
    ListNode* head;
    int size;
} LinkedList;

// 함수 선언
LinkedList* createLinkedList();
void destroyLinkedList(LinkedList* LS);
bool isEmptyLinkedList(LinkedList* LS);
int sizeLinkedList(LinkedList* LS);

void insertFirstLinkedList(LinkedList* LS, int item);
void insertLastLinkedList(LinkedList* LS, int item);
void insertAtLinkedList(LinkedList* LS, int at, int item);

int deleteFirstLinkedList(LinkedList* LS);
int deleteLastLinkedList(LinkedList* LS);
int deleteAtLinkedList(LinkedList* LS, int at);

void printLinkedList(LinkedList* LS);

#endif