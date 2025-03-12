#include<stdio.h>
#include <limits.h>

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int n,h;
    scanf("%d %d",&n,&h);
    int cost[n],val[n],max=0;
    for(int i=0;i<n;i++)
    {
        scanf("%d %d",&val[i],&cost[i]);
        if(val[i]>max)
            max=val[i];
    }
    int m=h+max;
    int dp[n+1][m+1];
    dp[0][0]=0;
    for(int i=1;i<=m;i++)
        dp[0][i]=INT_MAX;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j - val[i-1] >= 0&&dp[i][j - val[i-1]]!=INT_MAX)
            {
                dp[i][j] = min(dp[i][j], dp[i][j - val[i-1]] + cost[i-1]);
            }
        }
    }
    int ans=INT_MAX;
    for(int i=h;i<=m;i++)
        ans=min(ans,dp[n][i]);
    printf("%d",ans);
    return 0;
}
