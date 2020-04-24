#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ERROR -1

typedef int ElementType;
typedef int Position;

struct SNode {
    ElementType *Data;
    Position Top;
    int MaxSize;
};
typedef struct SNode *Stack;

Stack CreateEmpty(int MaxSize) {
    Stack S = (Stack) malloc(sizeof(struct SNode));
    S->MaxSize = MaxSize;
    S->Top = -1;    // 初始时栈空
    S->Data = (ElementType *) malloc(sizeof(ElementType) * MaxSize); // 开辟数组的空间
    return S;
}

bool IsFull(Stack S) {
    return S->Top == S->MaxSize - 1;
}

bool Push(Stack S, ElementType X) {
    if (IsFull(S)) {
        return false;
    } else {
        S->Data[++(S->Top)] = X;
        return true;
    }
}

bool IsEmpty(Stack S) {
    return S->Top == -1;
}

ElementType Pop(Stack S) {
    if (IsEmpty(S)) {
        return ERROR;
    } else {
        return S->Data[(S->Top)--];
    }
}

void CheckSequences(int M, int N, int K) {
    Stack S;
    int i, j;  // 入栈是有序的，且从1开始，i表示入栈到第i个元素，值也为i
    ElementType X, TopE;    // X是读入序列的每个元素，TopE 是栈顶元素
    bool valid; //序列是否有效

    S = CreateEmpty(M); // 创建一个大小为M的空栈
    while (K--) { // 共读取K个序列
        valid = true;   // 开始时默认有效
        i = 0;     // 开始时还没有入栈
        for (j = 0; j < N; j++) {   // 每行读N个
            scanf("%d", &X);    // X是已出栈栈顶元素，说明小于等于X的元素都已入栈了
            // 入栈的元素范围属于[i+1,X]
            while (i + 1 <= X) {
                if (!Push(S, i + 1)) {  // 检查是否能成功入栈
                    valid = false;
                    break;
                }
                i++;
            }
            TopE = Pop(S);    // 栈顶元素弹出后与X对比，看X是否是正确的出栈
            if (X != TopE) {
                valid = false;
            }
        }
        if (valid) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
}

int main() {
    int M, N, K;  // M是栈的大小, N是序列的长度，K是序列的数量
    scanf("%d %d %d", &M, &N, &K);
    CheckSequences(M, N, K);
    return 0;
}