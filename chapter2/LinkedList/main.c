#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define ERROR NULL;

typedef int ElementType;
typedef struct LNode *PtrToLNode;
struct LNode {
    ElementType Data;
    PtrToLNode Next;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;

/*查找 find */
Position Find(List L, ElementType X) {
    Position p = L; /*p指向L的第1个结点*/
    while (p != NULL && p->Data != X)
        p = p->Next;
    return p;
}

/*创建一个带头结点的空表*/
List MakeEmpty() {
    Position Head = malloc(sizeof(struct LNode));
    Head->Next = NULL;
    return Head;
}

void Print(List L) {
    Position p = L->Next;
    while (p) {
        printf("%d", p->Data);
        p = p->Next;
    }
    printf("\n");
}

/*带头结点的插入，在P之前插入新结点,这里默认L有头结点*/
bool Insert(List L, Position P, ElementType X) {
    Position pre = L; /*p指向头结点*/
    /*有头结点，不需要考虑表头插入时改变L的情况，直接先找到P的前一个结点*/
    while (pre && pre->Next != P)
        pre = pre->Next;
    if (pre == NULL) {
        return false;   /*P的前一个结点不存在，无法插入*/
    } else {
        /*找到了，插入新节点，将前一个结点指向新节点，新节点指向P*/
        Position tmp = (Position) malloc(sizeof(struct LNode));
        tmp->Data = X;
        tmp->Next = P;
        pre->Next = tmp;
        return true;
    }
}

/*带头结点的删除，P为要删除的结点的指针*/
bool Delete(List L, Position P) {
    Position pre = L;
    /*找到P的前一个结点*/
    while (pre && pre->Next != P) {
        pre = pre->Next;
    }
    if (pre == NULL) {
        /*没找到*/
        return false;
    } else {
        pre->Next = P->Next;
        free(P);
        return true;
    }
}


int main() {
    return 0;
}