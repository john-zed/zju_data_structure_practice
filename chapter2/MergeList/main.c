#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

/*L1和L2是给定的带头结点的单链表，其结点存储的数据是递增有序的；函数Merge要将L1和L2合并为一个非递减的整数序列。应直接使用原序列中的结点，返回归并后的带头结点的链表头指针。*/

/*
输入样例：
3
1 3 5
5
2 4 6 8 10
输出样例：
1 2 3 4 5 6 8 10
NULL
NULL
*/

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode Next;
};
typedef PtrToNode List;

List Read(); /* 细节在此不表 */
void Print(List L); /* 细节在此不表；空链表将输出NULL */

List Merge(List L1, List L2);

int main() {
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}

List Read() {
    List L, Rear;
    int N, i;
    scanf("%d", &N);
    if (!N) {
        return NULL;
    }
    L = (List) malloc(sizeof(struct Node));
    L->Next = NULL;
    Rear = L;
    while (N--) {
        scanf("%d", &i);
        PtrToNode NewCell = (PtrToNode) malloc(sizeof(struct Node));
        NewCell->Data = i;
        NewCell->Next = Rear->Next;
        Rear->Next = NewCell;
        Rear = NewCell;
    }
    return L;
}

void Print(List L) {
    if (!L || !L->Next) {
        printf("NULL");
    } else {
        while (L->Next) {
            printf("%d ", L->Next->Data);
            L = L->Next;
        }
    }
    printf("\n");
}

// 依次遍历L1和L2, 比较L1当前项和L2当前项i1和i2
// 若i1<=i2, 则把i1插到结果链表尾部, L1当前项前进一步
// 若i1>i2, 则把i2查到结果链表尾部，L2当前项前进一步
// 遍历结束一个链表后，将另一个链表剩余部分插入到结果链表
List Merge(List L1, List L2) {
    List L, Rear, t1, t2, Tmp;
    L = (List) malloc(sizeof(struct Node));  // L 指向结果链表的头结点
    L->Next = NULL;
    Rear = L;   // 开始时L为空，Rear指向头结点
    t1 = L1->Next;  // t1 指向链表1的第1个结点
    t2 = L2->Next;  // t2 指向链表2的第1个结点
    while (t1 && t2) {
        if (t1->Data <= t2->Data) { // L1当前结点t1小于等于L2当前结点t2
            Tmp = t1->Next;         // 保存t1的下一个结点
            t1->Next = Rear->Next;  // 将L1当前结点插入到结果链表的尾部，也就是Rear之后
            Rear->Next = t1;
            Rear = t1;              // Rear指向最后一个结点
            t1 = Tmp;
        } else {                    // L1当前结点t1大于L2当前结点t2
            Tmp = t2->Next;         // 保存t2的下一个结点
            t2->Next = Rear->Next;  // 将L2当前结点插入到结果链表的尾部，也就是Rear之后
            Rear->Next = t2;
            Rear = t2;              // Rear指向最后一个结点
            t2 = Tmp;               // t2指向下一个结点
        }
    }
    while (t1) {  // 将t1剩余结点依次插入结果链表尾部
        Tmp = t1->Next;
        t1->Next = Rear->Next;
        Rear->Next = t1;
        Rear = t1;
        t1 = Tmp;
    }
    while (t2) { // 将t2剩余结点依次插入结果链表尾部
        Tmp = t2->Next;
        t2->Next = Rear->Next;
        Rear->Next = t2;
        Rear = t2;
        t2 = Tmp;
    }

    // 将L1和L2置空
    L1->Next = NULL;
    L2->Next = NULL;
    return L;
}