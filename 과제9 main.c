#include <stdio.h>
#include <stdlib.h>
#include "arrayList.h"

int main(void) {
    arrayList* myArrayList;

    /* 일부러 작게 만들어서 realloc이 동작하는지 확인 */
    myArrayList = createArrayList(4);

    if (myArrayList == NULL) {
        printf("리스트 생성 실패\n");
        return 1;
    }

    if (sizeArrayList(myArrayList) == 0) {
        printf("Create ok\n");
    }

    printf("\n[삽입 테스트]\n");
    insertArrayList(myArrayList, 0, 10);
    insertArrayList(myArrayList, 1, 20);
    insertArrayList(myArrayList, 2, 30);
    insertArrayList(myArrayList, 0, 5);
    printArrayList(myArrayList);

    printf("\n[포화 상태에서 추가 삽입]\n");
    insertArrayList(myArrayList, 4, 40);   /* 여기서 확장 가능 */
    insertArrayList(myArrayList, 5, 50);
    printArrayList(myArrayList);

    printf("\n[중간 삽입 테스트]\n");
    insertArrayList(myArrayList, 2, 15);
    printArrayList(myArrayList);

    printf("\n[삭제 테스트]\n");
    printf("삭제된 값: %d\n", deleteArrayList(myArrayList, 0));
    printf("삭제된 값: %d\n", deleteArrayList(myArrayList, 2));
    printArrayList(myArrayList);

    printf("\n[조회 테스트]\n");
    printf("1번 위치 값: %d\n", getItemArrayList(myArrayList, 1));

    printf("\n[치환 테스트]\n");
    replaceItemArrayList(myArrayList, 1, 999);
    printArrayList(myArrayList);

    destroyArrayList(myArrayList);
    return 0;
}