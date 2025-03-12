#include <stdio.h>
#include <stdlib.h>

// 用于qsort的比较函数
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int minimumDeviation(int* nums, int numsSize) {
    // 创建一个足够大的数组来存储所有可能的数（包括翻倍后的奇数）
    int* temp = (int*)malloc(numsSize * 2 * sizeof(int));
    if (!temp) return -1; // 内存分配失败

    int tempSize = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] % 2 == 0) {
            temp[tempSize++] = nums[i];
        } else {
            temp[tempSize++] = nums[i] * 2;
        }
    }

    // 对temp数组进行排序
    qsort(temp, tempSize, sizeof(int), compare);

    int ans = temp[tempSize - 1] - temp[0];

    // 类似于Java中的while循环，但我们需要手动更新最大值和最小值
    while (ans > 0 && temp[tempSize - 1] % 2 == 0) {
        int max = temp[tempSize - 1];
        // 移除最大值
        tempSize--;
        // 添加最大值的一半
        temp[tempSize++] = max / 2;
        // 重新排序以找到新的最大值和最小值
        qsort(temp, tempSize, sizeof(int), compare);
        ans = temp[tempSize - 1] - temp[0];
    }

    free(temp); // 释放分配的内存
    return ans;
}

int main() {
    int n;
    scanf("%d",&n);
    int nums[n];
    for(int i=0;i<n;i++)
    {
        scanf("%d",&nums[i]);
    }
    printf("Minimum deviation: %d\n", minimumDeviation(nums, n));
    return 0;
}
