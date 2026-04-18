#include <stdio.h>
#include "arrayList.h"

int main() {
    arrayList* al;
    int menu;
    int pos, value;
    int result;

    al = createArrayList(5);
    if (al == NULL) {
        printf("리스트 생성 실패\n");
        return 1;
    }

    while (1) {
        printf("\n===== 순차 리스트 메뉴 =====\n");
        printf("1. 삽입\n");
        printf("2. 삭제\n");
        printf("3. 변경\n");
        printf("4. 출력\n");
        printf("5. 전체 삭제\n");
        printf("0. 종료\n");
        printf("메뉴 선택: ");
        scanf("%d", &menu);

        if (menu == 0) break;

        switch (menu) {
        case 1:
            printf("삽입 위치 입력: ");
            scanf("%d", &pos);
            printf("양의 정수 입력: ");
            scanf("%d", &value);

            if (insertArrayList(al, pos, value))
                printf("삽입 성공\n");
            else
                printf("삽입 실패\n");
            break;

        case 2:
            printf("삭제 위치 입력: ");
            scanf("%d", &pos);

            result = deleteArrayList(al, pos);
            if (result == -1)
                printf("삭제 실패\n");
            else
                printf("삭제된 값: %d\n", result);
            break;

        case 3:
            printf("변경 위치 입력: ");
            scanf("%d", &pos);
            printf("새 값 입력: ");
            scanf("%d", &value);

            if (replaceItemArrayList(al, pos, value))
                printf("변경 성공\n");
            else
                printf("변경 실패\n");
            break;

        case 4:
            printArrayList(al);
            break;

        case 5:
            clearArrayList(al);
            printf("리스트 전체 삭제 완료\n");
            break;

        default:
            printf("잘못된 입력입니다.\n");
        }
    }

    destroyArrayList(al);
    printf("프로그램 종료\n");

    return 0;
}