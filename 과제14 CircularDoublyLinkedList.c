#include "CircularDoublyLinkedList.h"
#include <stdio.h>
#include <stdlib.h>

// 1. 공백 리스트 생성 및 초기화
CDList* createList() {
    CDList* list = (CDList*)malloc(sizeof(CDList));
    if (list == NULL) {
        fprintf(stderr, "[오류] 리스트 메모리 할당 실패\n");
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

// 2. 모든 노드 메모리 순차 해제 (메모리 누수 방지)
void destroyList(CDList* list) {
    if (list == NULL) return;

    if (!isEmpty(list)) {
        Node* curr = list->head;
        int currentSize = list->size;

        // 원형 구조이므로 size만큼만 반복 수행하여 안전하게 해제
        for (int i = 0; i < currentSize; i++) {
            Node* nextNode = curr->next;
            free(curr);
            curr = nextNode;
        }
    }
    free(list); // 관리 구조체 해제
}

// 3. 공백 리스트 검사
bool isEmpty(CDList* list) {
    return (list == NULL || list->size == 0);
}

// 4. 리스트의 현재 크기 반환
int getSize(CDList* list) {
    if (list == NULL) return 0;
    return list->size;
}

// 5. 맨 앞에 노드 삽입 (index = 0)
bool insertFirst(CDList* list, ElementType item) {
    if (list == NULL) return false;

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return false;
    newNode->data = item;

    if (list->head == NULL) {
        // Case A: 리스트가 완전히 비어있는 경우 (자기 참조 원형 생성)
        newNode->next = newNode;
        newNode->prev = newNode;
        list->head = newNode;
    }
    else {
        // Case B: 기존 노드가 존재하는 경우
        Node* tail = list->head->prev; // O(1)로 tail 접근

        newNode->next = list->head;
        newNode->prev = tail;
        tail->next = newNode;
        list->head->prev = newNode;

        list->head = newNode; // Head 포인터 갱신
    }
    list->size++;
    return true;
}

// 6. 맨 뒤에 노드 삽입 (index = size)
bool insertLast(CDList* list, ElementType item) {
    if (list == NULL) return false;

    // 리스트가 비어있다면 맨 앞 삽입 로직과 동일
    if (list->head == NULL) {
        return insertFirst(list, item);
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return false;
    newNode->data = item;

    Node* tail = list->head->prev;

    // 링크 연결 조작 (원형 유지)
    newNode->next = list->head;
    newNode->prev = tail;
    tail->next = newNode;
    list->head->prev = newNode;

    list->size++;
    return true;
}

// 7. 임의의 위치(index)에 노드 삽입
bool insertAt(CDList* list, int index, ElementType item) {
    // 인덱스 범위 유효성 검사 (0 <= index <= size)
    if (list == NULL || index < 0 || index > list->size) return false;

    if (index == 0) return insertFirst(list, item);
    if (index == list->size) return insertLast(list, item);

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return false;
    newNode->data = item;

    // 삽입할 타겟 위치까지 순회 탐색
    Node* curr = list->head;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }

    // 포인터 링크 재배치
    Node* pre = curr->prev;
    newNode->prev = pre;
    newNode->next = curr;
    pre->next = newNode;
    curr->prev = newNode;

    list->size++;
    return true;
}

// 8. 임의의 위치(index)의 노드 삭제 및 데이터 반환
bool deleteAt(CDList* list, int index, ElementType* pDeletedItem) {
    // 언더플로우 및 인덱스 범위 유효성 검사 (0 <= index < size)
    if (list == NULL || isEmpty(list) || index < 0 || index >= list->size) return false;

    Node* toDelete = list->head;

    if (list->size == 1) {
        // Case A: 리스트에 노드가 단 하나만 존재했을 때의 예외 처리
        *pDeletedItem = toDelete->data;
        list->head = NULL;
    }
    else {
        // Case B: 일반적인 노드 삭제 상황
        for (int i = 0; i < index; i++) {
            toDelete = toDelete->next;
        }
        *pDeletedItem = toDelete->data;

        Node* pre = toDelete->prev;
        Node* nxt = toDelete->next;

        pre->next = nxt;
        nxt->prev = pre;

        // 만약 맨 앞(head) 노드가 삭제되었다면 head 포인터 갱신 필요
        if (index == 0) {
            list->head = nxt;
        }
    }

    free(toDelete); // 동적 할당 메모리 반환
    list->size--;
    return true;
}

// 9. 리스트 전체 데이터 포워드 스캔 출력
void printList(CDList* list) {
    if (list == NULL || isEmpty(list)) {
        printf("[안내] 현재 리스트가 비어있습니다.\n");
        return;
    }

    Node* curr = list->head;
    printf("임의 리스트 상태 (Size: %d) -> ", list->size);

    for (int i = 0; i < list->size; i++) {
        printf("[%d]", curr->data);
        if (i < list->size - 1) {
            printf(" <=> ");
        }
        curr = curr->next;
    }
    printf(" (정점 순환 구조)\n");
}