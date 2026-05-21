#include "browser_stack.h"

LinkedStack* createStack(void) {
    LinkedStack* stack = (LinkedStack*)malloc(sizeof(LinkedStack));
    if (stack != NULL) {
        stack->top = NULL;
    }
    return stack;
}

void destroyStack(LinkedStack* stack) {
    if (stack == NULL) return;

    Node* current = stack->top;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(stack);
}

int push(LinkedStack* stack, const char* url) {
    if (stack == NULL || isFull()) return 0;

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return 0;

    strncpy(newNode->url, url, MAX_URL_LEN - 1);
    newNode->url[MAX_URL_LEN - 1] = '\0';

    newNode->next = stack->top;
    stack->top = newNode;
    return 1;
}

char* pop(LinkedStack* stack, char* poppedUrl) {
    if (stack == NULL || isEmpty(stack)) return NULL;

    Node* temp = stack->top;
    strcpy(poppedUrl, temp->url);

    stack->top = temp->next;
    free(temp);

    return poppedUrl;
}

int isEmpty(LinkedStack* stack) {
    return (stack == NULL || stack->top == NULL);
}

int isFull(void) {
    Node* testNode = (Node*)malloc(sizeof(Node));
    if (testNode == NULL) {
        return 1;
    }
    free(testNode);
    return 0;
}

char* peek(LinkedStack* stack) {
    if (stack == NULL || isEmpty(stack)) return NULL;
    return stack->top->url;
}

void printStack(LinkedStack* stack) {
    if (stack == NULL || isEmpty(stack)) {
        printf("Stack is empty.\n");
        return;
    }
    Node* current = stack->top;
    printf("[Stack Top]\n");
    while (current != NULL) {
        printf(" -> %s\n", current->url);
        current = current->next;
    }
}