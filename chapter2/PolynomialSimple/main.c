#include <stdio.h>
#include <stdlib.h>

struct PolyNode {
    int coef;
    int expon;
    struct PolyNode *link;
};
typedef struct PolyNode *Polynomial;

Polynomial ReadPoly();

Polynomial Add(Polynomial P1, Polynomial P2);

Polynomial Multi(Polynomial P1, Polynomial P2);

void PrintPoly(Polynomial P);

void Attach(int coef, int expon, Polynomial *pRear);

int main() {
    Polynomial P1, P2, PP, PS;
    P1 = ReadPoly();
    P2 = ReadPoly();
    PP = Multi(P1, P2);
    PS = Add(P1, P2);
    PrintPoly(PP);
    PrintPoly(PS);
}

void PrintPoly(Polynomial P) {
    int flag = 0;
    if (!P) {
        printf("0 0\n");
        return;
    }
    while (P) {
        if (flag) {
            printf(" ");
        } else {
            flag = 1;
        }
        printf("%d %d", P->coef, P->expon);
        P = P->link;
    }
    printf("\n");
}

Polynomial ReadPoly() {
    Polynomial P, Rear, T;
    int N, c, e;
    scanf("%d", &N);
    if (!N) {
        return NULL;
    }
    P = (Polynomial) malloc(sizeof(struct PolyNode));
    P->link = NULL;
    Rear = P;
    while (N--) {
        scanf("%d %d", &c, &e);
        Attach(c, e, &Rear);
    }
    T = P;
    P = P->link;
    free(T);
    return P;
}

void Attach(int coef, int expon, Polynomial *pRear) {
    Polynomial T;
    if (!*pRear) {
        return;
    }
    T = (Polynomial) malloc(sizeof(struct PolyNode));
    T->coef = coef;
    T->expon = expon;
    T->link = NULL;
    (*pRear)->link = T;
    *pRear = T;
}

Polynomial Add(Polynomial P1, Polynomial P2) {
    Polynomial P, t1, t2, Rear, T;
    int c;
    P = (Polynomial) malloc(sizeof(struct PolyNode));
    P->link = NULL;
    Rear = P;
    t1 = P1;
    t2 = P2;
    while (t1 && t2) {
        if (t1->expon > t2->expon) {
            Attach(t1->coef, t1->expon, &Rear);
            t1 = t1->link;
        } else if (t1->expon == t2->expon) {
            c = t1->coef + t2->coef;
            if (c) {
                Attach(t1->coef + t2->coef, t1->expon, &Rear);
            }
            t1 = t1->link;
            t2 = t2->link;
        } else {
            Attach(t2->coef, t2->expon, &Rear);
            t2 = t2->link;
        }
    }
    while (t1) {
        Attach(t1->coef, t1->expon, &Rear);
        t1 = t1->link;
    }
    while (t2) {
        Attach(t2->coef, t2->expon, &Rear);
        t2 = t2->link;
    }
    T = P;
    P = P->link;
    free(T);
    return P;
}

Polynomial Multi(Polynomial P1, Polynomial P2) {
    Polynomial P, Rear, t1, t2, T;
    int c, e;
    if (!P1 || !P2) {
        return NULL;
    }
    P = (Polynomial) malloc(sizeof(struct PolyNode));
    P->link = NULL;
    Rear = P;
    t1 = P1;
    t2 = P2;
    while (t2) {
        Attach(t1->coef * t2->coef, t1->expon + t2->expon, &Rear);
        t2 = t2->link;
    }
    t1 = t1->link;
    while (t1) {
        Rear = P;
        t2 = P2;
        while (t2) {
            c = t1->coef * t2->coef;
            e = t1->expon + t2->expon;
            while (Rear->link && Rear->link->expon > e) {
                Rear = Rear->link;
            }
            if (Rear->link && Rear->link->expon == e) {
                if (Rear->link->coef + c) {
                    Rear->link->coef += c;
                } else {
                    T = Rear->link;
                    Rear->link = T->link;
                    free(T);
                }
            } else {
                T = (Polynomial) malloc(sizeof(struct PolyNode));
                T->coef = c;
                T->expon = e;
                T->link = Rear->link;
                Rear->link = T;
                Rear = Rear->link;
            }
            t2 = t2->link;
        }
        t1 = t1->link;
    }
    T = P;
    P = P->link;
    free(T);
    return P;
}