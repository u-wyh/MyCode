#include<stdio.h>
#include<stdbool.h>

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    int sg[n+1]; // 数组大小为 n+1
    bool appear[m+1]; // 假设 m 是可能的 sg 值的上限

    sg[0] = 0;
    for(int i = 1; i <= n; i++) { // 从 1 开始迭代，因为 sg[0] 已经设置
        for(int k = 0; k <= m; k++) {
            appear[k] = false;
        }
        for(int j = 1; j <= i && j <= m; j++) { // 确保 j 不会大于 m
            appear[sg[i-j]] = true;
        }
        for(int s = 0; s <= m; s++) {
            if(!appear[s]) {
                sg[i] = s;
                break; // 找到 s 后退出循环
            }
        }
    }
    for(int i = 0; i <= n; i++) { // 迭代到 n，因为 sg 数组现在有 n+1 个元素
        printf("%5d %5d\n",i, sg[i]);
    }
    printf("\n"); // 添加换行符以改善输出格式
    return 0;
}
