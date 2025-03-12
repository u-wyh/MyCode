/*
    这个函数是用于计算一个数组的可以整除k的最大子序列的和
    dp[i][j]的含义是数组的前i个数除以k余下j的最大子序列累加和
*/
#include<stdio.h>
#define Max 100

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int arr[Max];
    int i=0;
    printf("please enter the arr : ");
    while(scanf("%d",&arr[i++])==1);
    int n=i-1;
    int k;
    printf("please enter the k(suggest 7) : ");
    scanf("%d",&k);
    int dp[n+1][k];
    dp[0][0]=0;
    for(i=1;i<k;i++)
        dp[0][i]=-1;
    for(i=1;i<=n;i++)
    {
        int  cur = arr[i - 1] % k;
        for (int j = 0; j < k; j++) {
            dp[i][j] = dp[i - 1][j];
            // 这里求need是核心
            int need = cur <= j ? (j - cur) : (j - cur + k);
            // 或者如下这种写法也对
            // need = (7 + j - cur) % 7;
            if (dp[i - 1][need] != -1) {
                dp[i][j] = max(dp[i][j], dp[i - 1][need] + arr[i-1]);
            }
        }
    }
    printf("%5d\n",dp[n][0]);
    return 0;
}
