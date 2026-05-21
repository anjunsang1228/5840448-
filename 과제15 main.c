#include "browser_stack.h"

int main(void) {
    LinkedStack* browser = createStack();
    int menu;
    char inputUrl[MAX_URL_LEN];
    char poppedUrl[MAX_URL_LEN];

    if (browser == NULL) {
        fprintf(stderr, "Fatal Error: 스택 메모리 할당 실패\n");
        return 1;
    }

    while (1) {
        if (scanf("%d", &menu) != 1) {
            break;
        }
        
        while (getchar() != '\n');

        switch (menu) {
        case 1:
            printf("URL 입력:\n");
            if (fgets(inputUrl, sizeof(inputUrl), stdin)) {
                inputUrl[strcspn(inputUrl, "\r\n")] = '\0';
                if (push(browser, inputUrl)) {
                    printf("현재 창: %s\n", peek(browser));
                }
            }
            break;

        case 2:
            if (isEmpty(browser)) {
                printf("제거할 URL이 없습니다.\n");
                break;
            }

            pop(browser, poppedUrl);
            printf("이탈: %s\n", poppedUrl);

            if (isEmpty(browser)) {
                printf("브라우저가 종료되었습니다.\n");
                destroyStack(browser);
                return 0;
            }
            else {
                printf("현재 창: %s\n", peek(browser));
            }
            break;

        case 3:
            if (!isEmpty(browser)) {
                printf("현재 창: %s\n", peek(browser));
            }
            else {
                printf("현재 열려있는 창이 없습니다.\n");
            }
            break;

        default:
            break;
        }
    }

    destroyStack(browser);
    return 0;
}