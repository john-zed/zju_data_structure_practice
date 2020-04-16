#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ERROR -1

typedef int ElementType;
typedef int Position;

struct QNode {
    ElementType *Data;  /*存放元素的数组指针*/
    Position Front; /*队头*/
    Position Rear;  /*队尾*/
    int MaxSize;    /*存储元素的最大个数*/
};
typedef struct QNode *Queue;

Queue CreateEmpty(int MaxSize) {
    Queue Q = (Queue) malloc(sizeof(struct QNode));
    Q->Data = (ElementType *) malloc(sizeof(ElementType) * MaxSize);
    Q->MaxSize = MaxSize;
    Q->Front = Q->Rear = 0;
    return Q;
}

bool IsEmpty(Queue Q) {
    return Q->Front == Q->Rear;
}

bool IsFull(Queue Q) {
    return (Q->Rear + 1) % Q->MaxSize == Q->Front;
}

bool AddQ(Queue Q, ElementType X) {
    if (IsFull(Q)) {
        printf("full queue\n");
        return false;
    } else {
        Q->Rear = (Q->Rear + 1) % Q->MaxSize;
        Q->Data[Q->Rear] = X;
        return true;
    }
}

ElementType DeleteQ(Queue Q) {
    if (IsEmpty(Q)) {
        printf("empty queue\n");
        return ERROR;
    } else {
        Q->Front = (Q->Front + 1) % Q->MaxSize;
        return Q->Data[Q->Front];
    }
}

int main() {
    int i;
    Queue Q = CreateEmpty(5);
    for (i = 0; i < 6; i++) {
        AddQ(Q, i + 1);
    }
    for (i = 0; i < 6; i++) {
        printf("%d\n", DeleteQ(Q));
    }
    return 0;
}