#define _CRT_SECURE_NO_WARNINGS
#include "LinkedList.h"

int main() {
    LinkedList* list = createLinkedList();
    int choice, value, index;

    while (1) {
        printf("\n--- 연결 리스트 메뉴 ---\n");
        printf("1. 맨 앞에 추가\n");
        printf("2. 맨 뒤에 추가\n");
        printf("3. 특정 위치에 추가\n");
        printf("4. 특정 위치 삭제\n");
        printf("5. 전체 목록 출력\n");
        printf("6. 리스트 크기 확인\n");
        printf("0. 종료\n");
        printf("선택: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("추가할 정수 입력: ");
            scanf("%d", &value);
            insertFirstLinkedList(list, value);
            break;
        case 2:
            printf("추가할 정수 입력: ");
            scanf("%d", &value);
            insertLastLinkedList(list, value);
            break;
        case 3:
            printf("위치(index)와 정수 입력: ");
            scanf("%d %d", &index, &value);
            insertAtLinkedList(list, index, value);
            break;
        case 4:
            printf("삭제할 위치(index) 입력: ");
            scanf("%d", &index);
            value = deleteAtLinkedList(list, index);
            if (value != -1) printf("삭제된 값: %d\n", value);
            break;
        case 5:
            printLinkedList(list);
            break;
        case 6:
            printf("현재 노드 수: %d\n", sizeLinkedList(list));
            break;
        case 0:
            destroyLinkedList(list);
            printf("프로그램을 종료합니다.\n");
            return 0;
        default:
            printf("잘못된 입력입니다.\n");
        }
    }
}