#include <stdio.h>
#include <stdlib.h>

int minTaps(int n, int* ranges) {
    // 分配一个足够大的数组来存储每个位置能覆盖到的最右边界
    int* right = (int*)malloc((n + 1) * sizeof(int));
    if (right == NULL) {
        // 内存分配失败
        return -1;
    }
    for (int i = 0; i <= n; ++i) {
        right[i] = 0; // 初始化
    }

    // 填充right数组
    for (int i = 0; i <= n; ++i) {
        int start = i - ranges[i];
        start = start < 0 ? 0 : start; // 保证start不会小于0
        right[start] = i + ranges[i] > right[start] ? i + ranges[i] : right[start];
    }

    // 当前ans数量的水龙头打开，影响到的最右右边界
    int cur = 0;

    // 如果再多打开一个水龙头，影响到的最右边界
    int next = 0;

    // 打开水龙头的数量
    int ans = 0;

    for (int i = 0; i < n; i++) {
        // 先更新下一步的next
        next = next > right[i] ? next : right[i];

        // 来到i位置
        if (i == cur) {
            if (next > i) {
                cur = next;
                ans++;
            } else {
                // 如果无法继续覆盖，则返回-1
                free(right); // 释放内存
                return -1;
            }
        }
    }

    free(right); // 释放内存
    return ans;
}

int main() {
    // 示例用法
    int n ;
    scanf("%d",&n);
    int ranges[n];
    for(int i=0;i<n;i++)
    {
        scanf("%d",&ranges[i]);
    }
    int result = minTaps(n, ranges);
    printf("Minimum taps required: %d\n", result);
    return 0;
}
