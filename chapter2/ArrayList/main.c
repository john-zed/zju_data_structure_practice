#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 100
#define ERROR -1;

typedef int ElementType;
typedef int Position;
typedef struct LNode *List;
struct LNode {
    ElementType Data[MAXSIZE];
    Position Last;
};

/*初始化*/
List MakeEmpty() {
    List L = (List) malloc(sizeof(struct LNode));
    L->Last = -1;
    return L;
}

/*查找*/
Position Find(List L, ElementType X) {
    Position i = 0;
    while (i <= L->Last && L->Data[i] != X)
        i++;
    if (i > L->Last) {
        return ERROR;   /*如果没找到，返回错误信息*/
    } else {
        return i;       /*找到了，返回所在位置*/
    }
}

/*插入*/
/*这里P是在下标位置, 不是第P个元素位置*/
bool Insert(List L, ElementType X, Position P) {
    Position i;
    if (L->Last == MAXSIZE - 1) {   /*判断表是否满了*/
        printf("表已满");
        return false;
    }
    if (P < 0 || P > L->Last + 1) {  /*校验P的合法性, 注意P可以为Last + 1 表示插在尾部*/
        printf("位置不合法");
        return false;
    }
    /*将P以及之后所有元素向右移动一个位置，再把X放到P处*/
    for (i = L->Last; i >= P; i--) {
        L->Data[i + 1] = L->Data[i];
    }
    L->Data[P] = X;
    L->Last++;  /*Last指向最后一个元素*/
    return true;
}

/*删除*/
/*这里P是在下标位置, 不是第P个元素位置*/
bool Delete(List L, Position P) {
    Position i;
    if (L->Last == -1) {     /*空表不能删除*/
        printf("空表");
        return false;
    }
    if (P < 0 || P > L->Last) { /*P合法性校验*/
        printf("位置不合法");
        return false;
    }
    /*将P之后的元素都向左移动一个位置*/
    for (i = P; i < L->Last; i++) {
        L->Data[i] = L->Data[i + 1];
    }
    L->Last--;  /*Last指向最后一个元素*/
    return true;
}

void Print(List L) {
    printf("\n");
    Position i;
    for (i = 0; i <= L->Last; i++) {
        printf("%d\t", L->Data[i]);
    }
}

int main() {
    List L = MakeEmpty();
    Insert(L, 1, 0);
    Insert(L, 2, 0);
    Insert(L, 3, 0);
    Print(L);
    printf("%d", Find(L, 2));
    Delete(L, 2);
    Print(L);
    return 0;
}