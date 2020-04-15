#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ERROR -1;

typedef int ElementType;
typedef struct SNode *PtrToSNode;
struct SNode {
    ElementType Data;
    PtrToSNode Next;
};
typedef PtrToSNode Stack;

Stack CreateStack() {
    Stack S = (Stack) malloc(sizeof(struct SNode));
    S->Next = NULL;
    return S;
}

bool Push(Stack S, ElementType X) {
    PtrToSNode TmpCell = (PtrToSNode) malloc(sizeof(struct SNode));
    TmpCell->Data = X;
    TmpCell->Next = S->Next;
    S->Next = TmpCell;
    return true;
}

bool IsEmpty(Stack S) {
    return S->Next == NULL;
}

ElementType Pop(Stack S) {
    PtrToSNode FirstCell;
    ElementType TopElem;
    if (IsEmpty(S)) {
        printf("empty stack \n");
        return ERROR;
    } else {
        FirstCell = S->Next;
        TopElem = FirstCell->Data;
        S->Next = FirstCell->Next;
        free(FirstCell);
        return TopElem;
    }
}

int main() {
    Stack S = CreateStack();
    int i;
    for (i = 1; i <= 4; i++) {
        Push(S, i);
    }
    for (i = 1; i <= 5; i++) {
        printf("%d \n", Pop(S));
    }
    return 0;
}