#include "LinkedList.h"

// 공백 리스트 생성
LinkedList* createLinkedList() {
    LinkedList* LS = (LinkedList*)malloc(sizeof(LinkedList));
    LS->head = NULL;
    LS->size = 0;
    return LS;
}

// 모든 메모리 해제 및 구조체 소멸
void destroyLinkedList(LinkedList* LS) {
    ListNode* curr = LS->head;
    while (curr != NULL) {
        ListNode* next = curr->next;
        free(curr);
        curr = next;
    }
    free(LS);
}

bool isEmptyLinkedList(LinkedList* LS) {
    return (LS->head == NULL);
}

int sizeLinkedList(LinkedList* LS) {
    return LS->size;
}

// 맨 앞에 삽입
void insertFirstLinkedList(LinkedList* LS, int item) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->data = item;
    newNode->next = LS->head;
    LS->head = newNode;
    LS->size++;
}

// 맨 뒤에 삽입
void insertLastLinkedList(LinkedList* LS, int item) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->data = item;
    newNode->next = NULL;

    if (LS->head == NULL) {
        LS->head = newNode;
    }
    else {
        ListNode* curr = LS->head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = newNode;
    }
    LS->size++;
}

// 특정 위치(index)에 삽입 (0부터 시작)
void insertAtLinkedList(LinkedList* LS, int at, int item) {
    if (at < 0 || at > LS->size) {
        printf("잘못된 위치입니다.\n");
        return;
    }

    if (at == 0) {
        insertFirstLinkedList(LS, item);
    }
    else {
        ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
        newNode->data = item;

        ListNode* pre = LS->head;
        for (int i = 0; i < at - 1; i++) {
            pre = pre->next;
        }
        newNode->next = pre->next;
        pre->next = newNode;
        LS->size++;
    }
}

// 첫 번째 노드 삭제 및 데이터 반환
int deleteFirstLinkedList(LinkedList* LS) {
    if (isEmptyLinkedList(LS)) return -1;

    ListNode* oldNode = LS->head;
    int data = oldNode->data;
    LS->head = oldNode->next;
    free(oldNode);
    LS->size--;
    return data;
}

// 특정 위치의 노드 삭제 및 데이터 반환
int deleteAtLinkedList(LinkedList* LS, int at) {
    if (at < 0 || at >= LS->size || isEmptyLinkedList(LS)) {
        printf("삭제할 수 없는 위치입니다.\n");
        return -1;
    }

    if (at == 0) return deleteFirstLinkedList(LS);

    ListNode* pre = LS->head;
    for (int i = 0; i < at - 1; i++) {
        pre = pre->next;
    }
    ListNode* curr = pre->next;
    int data = curr->data;
    pre->next = curr->next;
    free(curr);
    LS->size--;
    return data;
}

// 모든 노드 데이터 출력
void printLinkedList(LinkedList* LS) {
    if (isEmptyLinkedList(LS)) {
        printf("리스트가 비어있습니다.\n");
        return;
    }
    ListNode* curr = LS->head;
    printf("List: ");
    while (curr != NULL) {
        printf("%d -> ", curr->data);
        curr = curr->next;
    }
    printf("NULL\n");
}