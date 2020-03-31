#include <stdio.h>

/*分治算法*/
int MaxSubseqSum3(int List[], int N) {
    /*保持与其他算法同样的函数接口*/
    return DivideAndConquer(List, 0, N - 1);
}

int DivideAndConquer(int List[], int left, int right) {
    /*左右半边的最大子列和*/
    int LeftMaxSum, RightMaxSum;
    /*跨越边界左右半边最大和*/
    int LeftBorderMaxSum, RightBorderMaxSum;
    /*跨越边界左右半边当前和*/
    int LeftBorderThisSum, RightBorerThisSum;
    /*中线位置*/
    int center;
    int i;

    /*递归结束条件, List中只有一个元素时*/
    if (left == right) {
        /*当前元素大于0时返回当前元素，否则返回0*/
        return List[left] > 0 ? List[left] : 0;
    }

    /*分割为左右两半, 左边是从left到center部分, 右边是从center+1到right部分*/
    center = (left + right) / 2;
    /*递归求得左右两半的最大子列和*/
    LeftMaxSum = DivideAndConquer(List, left, center);
    RightMaxSum = DivideAndConquer(List, center + 1, right);

    /*求跨越边界最大子列和*/
    LeftBorderMaxSum = RightBorderMaxSum = LeftBorderThisSum = RightBorerThisSum = 0;
    /*1. 从中线向左扫描，求左边最大和*/
    for (i = center; i >= left; i--) {
        LeftBorderThisSum += List[i];
        if (LeftBorderThisSum > LeftBorderMaxSum) {
            LeftBorderMaxSum = LeftBorderThisSum;
        }
    }
    /*2. 从中线向右扫描，求右边最大和*/
    for (i = center + 1; i <= right; i++) {
        RightBorerThisSum += List[i];
        if (RightBorerThisSum > RightBorderMaxSum) {
            RightBorderMaxSum = RightBorerThisSum;
        }
    }

    /*合并结果，取左半边最大子列和、右半边最大子列和、跨越边界最大子列和中的最大值，其中跨越边界最大子列和 = 左边最大和 + 右边最大和*/
    return MaxOf(LeftMaxSum, RightMaxSum, LeftBorderMaxSum + RightBorderMaxSum);
}

/*取三个数中的最大值*/
int MaxOf(int A, int B, int C) {
    return A > B ? (A > C ? A : C) : (B > C ? B : C);
}

/*在线处理算法*/
int MaxSubseqSum4(int List[], int N) {
    int ThisSum, MaxSum;
    ThisSum = MaxSum = 0;
    int i;
    for (i = 0; i < N; i++) {
        /*向右累加1项*/
        ThisSum += List[i];
        if (ThisSum > MaxSum) {
            /*发现更大和则更新当前结果*/
            MaxSum = ThisSum;
        } else if (ThisSum < 0) {
            /*当前子列和为负，则不可能使后面的部分和增大，直接抛弃*/
            ThisSum = 0;
        }
    }
    return MaxSum;
}

int main() {
    int N;
    int i;
    scanf("%d", &N);
    int List[N];

    for (i = 0; i < N; i++) {
        scanf("%d", &List[i]);
    }
    printf("%d", MaxSubseqSum3(List, N));
    return 0;
}