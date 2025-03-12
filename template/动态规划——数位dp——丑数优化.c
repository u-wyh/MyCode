//优化后的代码主要优化在节约空间上  没有设置更多的数组
#include<stdio.h>
#define max 1000

int min(int a,int b,int c)
{
    int min;
    min=a>b?b:a;
    min=min>c?c:min;
    return min;
}

int main()
{
    int n;
    scanf("%d",&n);
    int dp [n + 1];
    dp[1] = 1;
    printf("%5d",dp[1]);
    for (int i = 2, i2 = 1, i3 = 1, i5 = 1, a, b, c, cur; i <= n; i++) {
        a = dp[i2] * 2;
        b = dp[i3] * 3;
        c = dp[i5] * 5;
        cur = min(a, b, c);
        if (cur == a) {
            i2++;
        }
        if (cur == b) {
            i3++;
        }
        if (cur == c) {
            i5++;
        }
        dp[i] = cur;
        printf("%5d",dp[i]);
    }
    return dp[n];
    return 0;
}

