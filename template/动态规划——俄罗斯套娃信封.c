//背包问题  最长下降子序列
#include <stdio.h>
#include <stdlib.h>

// 结构体定义信封
typedef struct {
    int width;
    int height;
} Envelope;

// 比较函数，用于qsort
int compare(const void* a, const void* b) {
    Envelope* envA = (Envelope*)a;
    Envelope* envB = (Envelope*)b;
    if (envA->width != envB->width) {
        return envA->width - envB->width;
    } else {
        return envB->height - envA->height; // 注意这里是降序
    }
}

// 二分查找
int binarySearch(int* ends, int len, int num) {
    int l = 0, r = len - 1, m, ans = -1;
    while (l <= r) {
        m = (l + r) / 2;
        if (ends[m] >= num) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    return ans;
}

// 俄罗斯套娃信封问题
int maxEnvelopes(Envelope* envelopes, int envelopesSize) {
    if (envelopesSize == 0) return 0;

    // 使用qsort进行排序
    qsort(envelopes, envelopesSize, sizeof(Envelope), compare);

    int* ends = (int*)malloc(envelopesSize * sizeof(int));
    int len = 0;

    for (int i = 0; i < envelopesSize; i++) {
        int num = envelopes[i].height;
        int find = binarySearch(ends, len, num);
        if (find == -1) {
            ends[len++] = num;
        } else {
            ends[find] = num;
        }
    }

    int result = len;
    free(ends); // 释放内存
    return result;
}

int main() {
    // 示例输入
    Envelope envelopes[] = {{5, 4}, {6, 4}, {6, 7}, {2, 3}};
    int envelopesSize = sizeof(envelopes) / sizeof(envelopes[0]);

    // 调用函数并输出结果
    printf("最多能组成一组'俄罗斯套娃'信封的个数为: %d\n", maxEnvelopes(envelopes, envelopesSize));

    return 0;
}
