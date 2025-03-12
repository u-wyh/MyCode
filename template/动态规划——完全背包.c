#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int t,m;
    scanf("%d %d",&t,&m);
    int cost[m],val[m];
    for(int i=0;i<m;i++)
    {
        scanf("%d %d",&cost[i],&val[i]);
    }
    int  dp[t+1];
    for(int i=0;i<=t;i++)
        dp[i]=0;
    for (int i = 0; i < m; i++) {
        for (int j = cost[i]; j <= t; j++) {
            dp[j] = max(dp[j], dp[j - cost[i]] + val[i]);
        }
    }
    printf("%d\n",dp[t]);
    /*
    int dp[m+1][t+1];
    for(int i=0;i<=t;i++)
        dp[0][i]=0;
    for(int i=1;i<=m;i++)
    {
        for(int j=0;j<=t;j++)
        {
            dp[i][j]=dp[i-1][j];
            for(int k=1;k*cost[i-1]<=j;k++)
                dp[i][j]=max(dp[i][j],dp[i-1][j-k*cost[i-1]]+k*val[i-1]);
        }
    }
    printf("%d\n",dp[m][t]);
    */
    return 0;
}
