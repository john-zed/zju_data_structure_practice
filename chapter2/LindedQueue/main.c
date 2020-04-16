#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    struct Node *Next;
};
typedef PtrToNode Position;

struct QNode {
    Position Front, Rear;   /*队列的头尾指针，直接指向队头和队尾元素，无头结点*/
};
typedef struct QNode *Queue;

Queue CreateEmpty() {
    Queue Q = (Queue) malloc(sizeof(struct QNode));
    Q->Front = Q->Rear = NULL;
    return Q;
}

bool IsEmpty(Queue Q) {
    return Q->Front == NULL;
}

void AddQ(Queue Q, ElementType X) {
    Position NewCell = (Position) malloc(sizeof(struct Node));
    NewCell->Data = X;
    NewCell->Next = NULL;
    if (IsEmpty(Q)) {   /*插入第一个元素*/
        Q->Front = Q->Rear = NewCell; /*队头队尾指向第一个元素*/
    } else {
        Q->Rear->Next = NewCell;
        Q->Rear = NewCell;
    }
}

#define ERROR -1

ElementType DeleteQ(Queue Q) {
    Position FrontCell;
    ElementType FrontElem;
    if (IsEmpty(Q)) {
        printf("empty queue\n");
        return ERROR;
    } else {
        FrontCell = Q->Front;
        if (Q->Front == Q->Rear) {   /*队列中只有一个元素*/
            Q->Front = Q->Rear = NULL; /*删除后队列置空*/
        } else {
            Q->Front = Q->Front->Next;
        }
        FrontElem = FrontCell->Data;
        free(FrontCell);    /*释放被删除结点*/
        return FrontElem;
    }
}


int main() {
    Queue Q = CreateEmpty();
    int i;
    for (i = 0; i < 5; i++) {
        AddQ(Q, i + 1);
    }
    for (i = 0; i < 6; i++) {
        printf("%d\n", DeleteQ(Q));
    }

    return 0;
}