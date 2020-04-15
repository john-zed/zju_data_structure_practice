#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ERROR -1;

typedef int ElementType;
typedef int Position;
struct SNode {
    ElementType *Data;  /*存储元素的数组*/
    Position Top;   /*栈顶指针*/
    int MaxSize;    /*堆栈最大容量*/
};
typedef struct SNode *Stack;

Stack CreateStack(int MaxSize) {
    Stack S = (Stack) malloc(sizeof(struct SNode));
    S->Data = (ElementType *) malloc(sizeof(ElementType) * MaxSize);
    S->Top = -1;
    S->MaxSize = MaxSize;
    return S;
}

bool IsFull(Stack S) {
    return S->Top == S->MaxSize - 1;
}

bool IsEmpty(Stack S) {
    return S->Top == -1;
}

bool Push(Stack S, ElementType X) {
    if (IsFull(S)) {
        printf("full stack \n");
        return false;
    } else {
        S->Data[++(S->Top)] = X;
        return true;
    }
}

ElementType Pop(Stack S) {
    if (IsEmpty(S)) {
        printf("empty stack \n");
        return ERROR;
    } else {
        return S->Data[(S->Top)--];
    }
}

int main() {
    Stack S = CreateStack(3);
    int i;
    for (i = 1; i <= 4; i++) {
        Push(S, i);
    }
    for (i = 0; i < 4; i++) {
        printf("%d \n", Pop(S));
    }
    return 0;
}