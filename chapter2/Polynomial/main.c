#include <stdio.h>
#include <stdlib.h>

/*多项式乘法与加法*/

struct PolyNode {
    int coef;   // 系数
    int expon;  // 指数
    struct PolyNode *link;  // 下一项
};
typedef struct PolyNode *Polynomial;

Polynomial ReadPoly();

Polynomial Multi(Polynomial P1, Polynomial P2);

Polynomial Add(Polynomial P1, Polynomial P2);

void PrintPoly(Polynomial P);

int Compare(int a, int b);

void Attach(int coef, int expon, Polynomial *pRear);

int main() {
    Polynomial P1, P2, PP, PS;

    P1 = ReadPoly();    // 读取多项式
    P2 = ReadPoly();
    PS = Add(P1, P2);   // 求和
    PP = Multi(P1, P2); // 求积
    PrintPoly(PP);
    PrintPoly(PS);
    return 0;
}

// 读取多项式
Polynomial ReadPoly() {
    Polynomial P, Rear, Tmp;
    int N, c, e;  // 项数
    scanf("%d", &N);
    if (N < 1) {
        return NULL;
    }

    P = (Polynomial) malloc(sizeof(struct PolyNode));   // 多项式用不带头结点的链表实现。只开始时构造一个头结点，以便在尾部Rear插入时不需要判断Rear是否为NULL。
    P->link = NULL;
    Rear = P;   // Rear是指向最后一项的指针，开始时多项式为空，指向空的头结点
    while (N--) {
        // 读入系数和指数
        scanf("%d %d", &c, &e);
        Tmp = (Polynomial) malloc(sizeof(struct PolyNode));  // 构造新结点
        Tmp->coef = c;
        Tmp->expon = e;
        Tmp->link = Rear->link; // 将新结点插入到Rear指向的最后一项之后
        Rear->link = Tmp;
        Rear = Tmp; // Rear指向新插入的结点，也就是最后一个结点
    }
    // 清理头结点
    Tmp = P;
    P = P->link;
    free(Tmp);
    return P;
}

// 打印多项式
void PrintPoly(Polynomial P) {
    int flag = 0;
    if (!P) {
        printf("0 0\n");
        return;
    }
    while (P) {
        if (flag)           // 第一项前面不打印空格，其余项打印完加一个空格
            printf(" ");
        else
            flag = 1;
        printf("%d %d", P->coef, P->expon);
        P = P->link;
    }
    printf("\n");
}

// 多项式求和
Polynomial Add(Polynomial P1, Polynomial P2) {
    Polynomial P, t1, t2, Rear, Tmp;

    P = (Polynomial) malloc(sizeof(struct PolyNode));   // P为结果多项式，为了方便插入，开始时构造一个头结点
    P->link = NULL;
    Rear = P;   // Rear指向结果多项式最后一项，开始时结果多项式为空，Rear指向头结点
    t1 = P1;
    t2 = P2;
    while (t1 && t2) {  // 遍历P1和P2
        switch (Compare(t1->expon, t2->expon)) {
            case 1: // P1当前项t1指数较大，插入到结果多项式尾部，t1指向下一项
                Attach(t1->coef, t1->expon, &Rear);
                t1 = t1->link;
                break;
            case 0: // P2与P1当前项t1、t2指数相等，合并当前项，t1、t2都指向下一项,系数相加不为0时插入到结果多项式尾部，
                if (t1->coef + t2->coef) {
                    Attach(t1->coef + t2->coef, t1->expon, &Rear);
                }
                t1 = t1->link; // !!! 无论合并后的项系数是否为0，t1、t2都要指向下一项
                t2 = t2->link;
                break;
            case -1:    // P2当前项t2较大，插入到结果多项式尾部，t2指向下一项
                Attach(t2->coef, t2->expon, &Rear);
                t2 = t2->link;
                break;
            default:
                break;
        }
    }
    while (t1) {    // P1或P2剩余项插入到结果多项式尾部
        Attach(t1->coef, t1->expon, &Rear);
        t1 = t1->link;
    }
    while (t2) {
        Attach(t2->coef, t2->expon, &Rear);
        t2 = t2->link;
    }
    Tmp = P;    // 清理头结点
    P = P->link;
    free(Tmp);
    return P;
}

// 比较两数大小
int Compare(int a, int b) {
    return a > b ? 1 : (a == b ? 0 : -1);
}

// 向多项式尾部插入一项
void Attach(int coef, int expon, Polynomial *pRear) {    // C语言函数值传递，要改变Rear指针，需要使用指向Rear的指针
    Polynomial P;   // 新结点

    if (!*pRear) return;    //Rear指针是NULL, 无法插入
    P = (Polynomial) malloc(sizeof(struct PolyNode));    // 构造新结点
    P->coef = coef;
    P->expon = expon;
    P->link = (*pRear)->link;   // 新结点插入到Rear之后
    (*pRear)->link = P;
    *pRear = P;     // Rear指向新插入项，及最后一项
}

Polynomial Multi(Polynomial P1, Polynomial P2) {
    Polynomial P, t1, t2, Rear, Tmp;
    int c, e;

    if (!P1 || !P2) // 有一个多项式为空，结果就为空
        return NULL;
    P = (Polynomial) malloc(sizeof(struct PolyNode));   // 结果多项式也是不含头结点的链表，这里构造一个头结点，是为了方便插入操作
    P->link = NULL;
    Rear = P;
    t1 = P1;
    t2 = P2;
    while (t2) {    // 用P1的第1项和P2各项相乘，构成初始结果多项式
        Attach(t1->coef * t2->coef, t1->expon + t2->expon, &Rear);
        t2 = t2->link;
    }
    t1 = t1->link;  // t1指向P1第2项
    while (t1) {    // P1各项与P2各项相乘，得到当前项积，逐个插入到结果多项式中
        t2 = P2;    // t2重新指向P2第1项
        Rear = P;   // P1某项与P2各项相乘开始时，都将Rear指向结果多项式的头结点，Rear->link指向多项式某一项，Rear指向这一项的前一项
        while (t2) {
            c = t1->coef * t2->coef;    // 当前的积的系数
            e = t1->expon + t2->expon;  // 当前项积的指数
            while (Rear->link && Rear->link->expon > e)     // 从结果多项式的第一项(指数最大项)开始，寻找结果多项式指数不大于当前项积的指数的那一项
                Rear = Rear->link;
            // 循环结束时有Rear->link指向的项的指数<=当前项积的指数
            if (Rear->link && Rear->link->expon == e) {
                // 如果结果多项式这一项的指数与当前项积的指数相等，那么应该合并结果多项式的这一项和当前项的积，
                // !!! 注意Rear->link可能为空，说明结果多项式每一项系数都比当前项积的指数大，插在结果多项式尾部
                if (Rear->link->coef + c)   // 合并后系数不为0
                    Rear->link->coef += c;
                else {   // 合并后系数为0，删掉这一项
                    Tmp = Rear->link;
                    Rear->link = Tmp->link;
                    free(Tmp);
                }
            } else {    // 如果结果多项式这一项的指数小于当前项积的指数，则将当前项积插入到这一项之前，也可能是结果多项式每一项指数都比较大，插到尾部，同样是插到Rear之后
                Tmp = (Polynomial) malloc(sizeof(struct PolyNode)); // 构造新结点保存当前项积
                Tmp->coef = c;
                Tmp->expon = e;
                Tmp->link = Rear->link;
                Rear->link = Tmp;
            }
            t2 = t2->link;
        }
        t1 = t1->link;
    }

    t2 = P;    // 清理头结点
    P = P->link;
    free(t2);
    return P;
}