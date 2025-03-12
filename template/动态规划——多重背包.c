#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int cost[n],val[n],c[n];
    for(int i=0;i<n;i++)
        scanf("%d %d %d",&val[i],&cost[i],&c[i]);
    int dp[n+1][m+1];
    for(int i=0;i<=m;i++)
        dp[0][i]=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
        {
            dp[i][j]=dp[i-1][j];
            for(int k=1;k<=c[i-1]&&j>=k*cost[i-1];k++)
                dp[i][j]=max(dp[i][j],dp[i-1][j-k*cost[i-1]]+k*val[i-1]);
        }
    }
    printf("%d\n",dp[n][m]);
    return 0;
}
