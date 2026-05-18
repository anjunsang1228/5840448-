#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "CircularDoublyLinkedList.h"

// 입력 버퍼를 비워 비정상적인 무한 루프를 방지하는 함수
void clearInputBuffer() {
    while (getchar() != '\n');
}

void printMenu() {
    printf("\n=========================================\n");
    printf("  [자료구조] 이중 원형 연결 리스트 제어 메뉴 \n");
    printf("=========================================\n");
    printf(" 1. 맨 앞에 데이터 추가\n");
    printf(" 2. 맨 뒤에 데이터 추가\n");
    printf(" 3. 지정 위치(Index)에 데이터 추가\n");
    printf(" 4. 지정 위치(Index) 데이터 삭제 및 출력\n");
    printf(" 5. 리스트 전체 목록 출력\n");
    printf(" 6. 리스트 현재 크기(Size) 확인\n");
    printf(" 0. 프로그램 종료 (모든 메모리 자원 해제)\n");
    printf("=========================================\n");
    printf("선택 명령 입력 -> ");
}

int main() {
    CDList* list = createList();
    if (list == NULL) return 1;

    int menuChoice = -1;
    int dataInput, indexInput;
    ElementType poppedData;

    while (true) {
        printMenu();
        if (scanf("%d", &menuChoice) != 1) {
            printf("[경고] 올바른 숫자를 입력하십시오.\n");
            clearInputBuffer();
            continue;
        }

        if (menuChoice == 0) {
            printf("[종료] 할당된 모든 동적 메모리를 시스템에 반환하고 종료합니다.\n");
            destroyList(list);
            break;
        }

        switch (menuChoice) {
        case 1:
            printf("추가할 정수 입력: ");
            scanf("%d", &dataInput);
            if (insertFirst(list, dataInput)) {
                printf(">> 성공: 맨 앞에 [%d] 노드가 정상 삽입되었습니다.\n", dataInput);
            }
            break;

        case 2:
            printf("추가할 정수 입력: ");
            scanf("%d", &dataInput);
            if (insertLast(list, dataInput)) {
                printf(">> 성공: 맨 뒤에 [%d] 노드가 정상 삽입되었습니다.\n", dataInput);
            }
            break;

        case 3:
            printf("삽입 인덱스 위치(0 ~ %d) 입력: ", getSize(list));
            scanf("%d", &indexInput);
            printf("추가할 정수 입력: ");
            scanf("%d", &dataInput);
            if (insertAt(list, indexInput, dataInput)) {
                printf(">> 성공: 인덱스 [%d] 위치에 [%d] 노드가 삽입되었습니다.\n", indexInput, dataInput);
            }
            else {
                printf(">> 실패: 잘못된 인덱스 범위이거나 메모리가 부족합니다.\n");
            }
            break;

        case 4:
            if (isEmpty(list)) {
                printf(">> 실패: 리스트가 비어있어 삭제 연산을 수행할 수 없습니다.\n");
                break;
            }
            printf("삭제 인덱스 위치(0 ~ %d) 입력: ", getSize(list) - 1);
            scanf("%d", &indexInput);
            if (deleteAt(list, indexInput, &poppedData)) {
                printf(">> 성공: 인덱스 [%d] 노드가 삭제되었습니다. [삭제 데이터: %d]\n", indexInput, poppedData);
            }
            else {
                printf(">> 실패: 해당 인덱스는 리스트의 범위를 벗어납니다.\n");
            }
            break;

        case 5:
            printList(list);
            break;

        case 6:
            printf(">> 현재 리스트에 보존된 총 노드 개수: %d개\n", getSize(list));
            break;

        default:
            printf("[경고] 정의되지 않은 메뉴 코드입니다. (0~6 사이 선택)\n");
            break;
        }
    }

    return 0;
}