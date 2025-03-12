#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int maxprofit(int *nums,int n,int k)
{
    int dp[k+1][n+1];
    for(int i=0;i<=n;i++)
        dp[0][i]=0;
    for(int i=1;i<=k;i++)
        dp[i][0]=0;
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] = dp[i][j - 1];
            for (int p = 0; p < j; p++) {
                dp[i][j] = max(dp[i][j], dp[i - 1][p] + nums[j] - nums[p]);
            }
        }
    }
    return dp[k][n];
}

int maxprofit2(int *nums,int n,int k)
{

    int dp [k + 1][n + 1];
    for(int i=0;i<=n;i++)
        dp[0][i]=0;
    for(int i=1;i<=k;i++)
        dp[i][0]=0;
    for (int i = 1, best; i <= k; i++) {
        best = dp[i - 1][0] - nums[0];
        for (int j = 1; j <=n; j++) {
            // 用best变量替代了枚举行为
            dp[i][j] = max(dp[i][j - 1], best + nums[j]);
            best = max(best, dp[i - 1][j] - nums[j]);
        }
    }
    return dp[k][n];
}

int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
    int nums[n+1];
    for(int i=1;i<=n;i++)
        scanf("%d",&nums[i]);
    printf("%d\n",maxprofit(nums,n,k));
    printf("%d\n",maxprofit2(nums,n,k));
    return 0;
}
