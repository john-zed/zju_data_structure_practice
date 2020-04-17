#include <stdio.h>

/* a small trick to print a array in format  a,b,c,d,e */

// 打印格式如1,2,3,4,5
// result format like 1,2,3,4,5
void PrintArray(int *A, int N) {
    int flag = 0;
    int i;
    for (i = 0; i < N; i++) {
        if (flag)
            printf(",");
        else
            flag = 1;
        printf("%d", A[i]);
    }
}

int main() {
    int A[] = {1, 2, 3, 4, 5};
    PrintArray(A, 5);
    return 0;
}

