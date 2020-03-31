#include <stdio.h>

int main() {
    int N;
    int i;
    scanf("%d", &N);
    int List[N];
    for (i = 0; i < N; i++) {
        scanf("%d", &List[i]);
    }

    int MaxSum, ThisSum;
    int left, right;
    int start;
    /*最大子列和初始化为第一个元素*/
    MaxSum = List[0];
    ThisSum = 0;
    left = start = 0;
    right = N - 1;
    for (i = 0; i < N; i++) {
        /*向右累加一项*/
        ThisSum += List[i];
        if (ThisSum > MaxSum) {
            /*当前子列和更大，则更新最大子列和*/
            MaxSum = ThisSum;
            /*更新子列和起止位置，left为新的起始位置，right为当前位置*/
            left = start;
            right = i;
        } else if (ThisSum < 0) {
            /*当前子列和为负，那么不可能使后面的和增加了，因此需要抛弃掉，从i + 1 重新计算*/
            ThisSum = 0;
            /*记录新的起始位置，不能直接更新left*/
            start = i + 1;
        }
    }

    /*全为负数的话，最大子列和为0*/
    if (MaxSum < 0) {
        MaxSum = 0;
    }

    printf("%d %d %d", MaxSum, List[left], List[right]);

    return 0;
}