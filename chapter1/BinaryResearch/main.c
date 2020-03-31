#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define NotFound 0
typedef int ElementType;

typedef int Position;
typedef struct LNode *List;
struct LNode {
    ElementType Data[MAXSIZE];
    Position Last; /* 保存线性表中最后一个元素的位置 */
};

List ReadInput(); /* 裁判实现，细节不表。元素从下标1开始存储 */
Position BinarySearch(List L, ElementType X);

int main() {
    List L;
    ElementType X;
    Position P;

    L = ReadInput();
    scanf("%d", &X);
    P = BinarySearch(L, X);
    printf("%d\n", P);

    return 0;
}

Position BinarySearch(List L, ElementType X) {
    int left, right, center;

    left = 1;
    right = L->Last;

    /*用小于等于是考虑到在尾部找到的情况*/
    while (left <= right) {
        /*取中点*/
        center = (left + right) / 2;

        if (L->Data[center] == X) {
            /*中间值等于X，返回下标*/
            return center;
        } else if (L->Data[center] > X) {
            /*中间值比X大，在左半部查找*/
            right = center - 1;
        } else if (L->Data[center] < X) {
            /*中间值比X小，在右半部查找*/
            left = center + 1;
        }
    }

    /*前面没返回说明没找到*/
    return NotFound;
}
