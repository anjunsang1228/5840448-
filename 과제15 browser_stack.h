#define _CRT_SECURE_NO_WARNINGS

#ifndef __BROWSER_STACK_H__
#define __BROWSER_STACK_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LEN 256

typedef struct Node {
    char url[MAX_URL_LEN];
    struct Node* next;
} Node;

typedef struct LinkedStack {
    Node* top;
} LinkedStack;

LinkedStack* createStack(void);
void destroyStack(LinkedStack* stack);
int push(LinkedStack* stack, const char* url);
char* pop(LinkedStack* stack, char* poppedUrl);
int isEmpty(LinkedStack* stack);
int isFull(void);
char* peek(LinkedStack* stack);
void printStack(LinkedStack* stack);

#endif
