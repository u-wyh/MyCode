#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#define MAX 1000000+5

// 计算next数组
int* nextArray(const char *s, int m) {
    if (m == 1) {
        int *next = (int*)malloc(sizeof(int));
        next[0] = -1;
        return next;
    }

    int *next = (int*)malloc(m * sizeof(int));
    next[0] = -1;
    next[1] = 0;

    int i = 2, cn = 0;
    while (i < m) {
        if (s[i - 1] == s[cn]) {
            next[i++] = ++cn;
        } else if (cn > 0) {
            cn = next[cn];
        } else {
            next[i++] = 0;
        }
    }

    return next;
}

// KMP算法的核心函数
int kmp(const char *s1, const char *s2) {
    int n = strlen(s1), m = strlen(s2), x = 0, y = 0;
    int *next = nextArray(s2, m);
    // s1中当前比对的位置是x
    // s2中当前比对的位置是y
    while (x < n && y < m) {
        if (s1[x] == s2[y]) {
            x++;
            y++;
        } else if (y == 0) {
            x++;
            //表示s2已经在第一个位置了
        } else {
            y = next[y];
            //表示s2往前跳
        }
    }

    free(next); // 释放next数组占用的内存
    return y == m ? x - y : -1;
}

// 主函数，用于测试
int main() {
    const char s1[MAX],s2[MAX];
    scanf("%s",s1);
    scanf("%s",s2);
    int result = kmp(s1, s2);
    if (result != -1) {
        printf("Found at index: %d\n", result);
    } else {
        printf("Not found\n");
    }

    return 0;
}
