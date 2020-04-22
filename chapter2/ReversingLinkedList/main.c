#include <stdio.h>

#define MaxSize 100000

typedef int Position;
struct Node {   // 每个数组中的分量有两个元素，结点值和下一个结点的地址
    int Data;
    Position Next;
};

void ReadData(struct Node Nodes[], int *pPortal, int *pN, int *pK) {
    Position Address, Next;
    int Data, N;
    scanf("%05d %d %d", pPortal, &N, pK);   // 读入第一个结点的地址、结点数量、K的值
    *pN = N;
    while (N--) {
        scanf("%05d %d %05d", &Address, &Data, &Next);
        Nodes[Address].Data = Data; // 用数组模拟链表，下标代表链表地址，数组分量的Next代表下一个结点的地址
        Nodes[Address].Next = Next;
    }
}

void PrintNode(Position Address, int Data, int flag) {
    if (!flag) { // 不是打印第一个元素
        printf("%05d\n", Address);
    }
    printf("%05d %d ", Address, Data);
}

void Pop(struct Node *Nodes, Position *pTop, int flag) {
    if (*pTop == -1) {
        return; // 空栈
    }
    PrintNode(*pTop, Nodes[*pTop].Data, flag);  // 打印栈顶的结点
    *pTop = Nodes[*pTop].Next;  // 栈顶指向下一个结点
}

void Push(struct Node *Nodes, Position *pTop, Position Address, int Data) {
    Nodes[Address].Data = Data;     // 相当于申请一个新结点
    Nodes[Address].Next = *pTop;    // 新结点下一个指向栈顶结点
    *pTop = Address;    // 栈顶指向新结点
}

int Count(Position Portal, struct Node Nodes[]) {
    int count;
    for (count = 0; Portal != -1; Portal = Nodes[Portal].Next, count++);    // 相当于指针不为NULL时，就一直遍历
    return count;
}

// 翻转链表， Portal 为链表的入口地址，指向第一个结点，N是链表的长度
void ReverseList(Position Portal, int N, int K, struct Node Nodes[]) {
    Position P, Top;  //Top代表栈顶指针
    Top = -1;   // 开始时栈空，栈顶指向空指针，-1表示空指针
    int i, j, length, flag; // flag 是否是打印第一个元素 ，1表示是，0表示否
    flag = 1;   // 开始时打印第一个元素
    length = 0;   // 栈中元素的个数
    struct Node Stack[MaxSize]; // 模拟一个空栈
    for (P = Portal, i = 0; P != -1; P = Nodes[P].Next, i++) {
        if (length + N - i >= K) {  // 剩余元素个数是N-i, 栈中元素数量是length, 当剩余元素+栈中元素>=K时，可以入栈并满足能入栈K个
            // 入栈
            Push(Stack, &Top, P, Nodes[P].Data);
            length++;
        } else {
            PrintNode(P, Nodes[P].Data, flag);  // 剩余元素+栈中元素不足K, 直接顺序打印
        }
        if ((i + 1) % K == 0) {   // 栈中已经有了K个元素
            for (j = 0; j < K; j++) { // 出栈K个
                Pop(Stack, &Top, flag);
                if (flag == 1) {    // 出栈并打印了一个之后，不再是第一个元素
                    flag = 0;
                }
            }
            length = 0;
        }
    }
    printf("-1\n");
}

int main() {
    Position Portal;    // 用数组模拟链表，用数组下标模拟指针，Portal链表入口，指向第一个结点
    int N, K;   // N结点数量，K是每K个翻转一次
    struct Node Nodes[MaxSize]; // 由于地址是5位数的正整数，那么数组最大为100000, 下标范围是0~99999
    ReadData(Nodes, &Portal, &N, &K);   // 读入结点
    N = Count(Portal, Nodes);   // 计算链表的真实长度，输入中可能有不在链上的结点
    ReverseList(Portal, N, K, Nodes);  // 逆转链表
    return 0;
}