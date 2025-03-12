#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXV 100001
#define MAXN 20001

int factors[MAXV];
int father[MAXN];
int size[MAXN];
int n;

// 初始化factors数组和并查集
void build(int arrSize) {
    memset(factors, -1, sizeof(factors));
    for (int i = 0; i < arrSize; i++) {
        father[i] = i;
        size[i] = 1;
    }
}

// 查找根节点
int find(int i) {
    if (i != father[i]) {
        father[i] = find(father[i]);
    }
    return father[i];
}

// 合并两个集合
void unionSet(int x, int y) {
    int fx = find(x);
    int fy = find(y);
    if (fx != fy) {
        father[fx] = fy;
        size[fy] += size[fx];
    }
}

// 获取最大集合的大小
int maxSize() {
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (size[i] > ans) {
            ans = size[i];
        }
    }
    return ans;
}

// 打印n的所有质因子
void printFactors(int n) {
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            printf("%d\n", i);
            while (n % i == 0) {
                n /= i;
            }
        }
    }
    if (n > 1) {
        printf("%d\n", n);
    }
}

// 计算给定数组的最大连通组件大小
int largestComponentSize(int* arr, int arrSize) {
    n = arrSize;
    build(arrSize);

    for (int i = 0; i < arrSize; i++) {
        int x = arr[i];
        for (int j = 2; j * j <= x; j++) {
            if (x % j == 0) {
                if (factors[j] == -1) {
                    factors[j] = i;
                } else {
                    unionSet(factors[j], i);
                }
                while (x % j == 0) {
                    x /= j;
                }
            }
        }
        if (x > 1) {
            if (factors[x] == -1) {
                factors[x] = i;
            } else {
                unionSet(factors[x], i);
            }
        }
    }

    return maxSize();
}

int main() {
    int n;
    scanf("%d",&n);
    int arr[n] ; // 示例数组
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }
    int size = sizeof(arr) / sizeof(arr[0]);
    int maxSize = largestComponentSize(arr, size);
    printf("最大连通组件的大小为: %d\n", maxSize);

    // 另外，打印4012100的所有质因子
    //printFactors(4012100);

    return 0;
}
