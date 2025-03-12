#include<stdio.h>
#define Max 100

static int cost[Max],val[Max];

int max(int a,int b)
{
    return a>b?a:b;
}

int compute(int n,int t)
{
    int dp[n+1][t+1];
    for(int i=0;i<=t;i++)
    {
        dp[0][i]=0;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=t;j++)
        {
            dp[i][j]=dp[i-1][j];
            if(j>=cost[i-1])
                dp[i][j]=max(dp[i-1][j],dp[i-1][j-cost[i-1]]+val[i-1]);
        }
    }
    return dp[n][t];
}

int main()
{
    int i=0;
    printf("please enter the cost and value : ");
    while(scanf("%d %d",&cost[i],&val[i])==2)
        i++;
    int n=i;
    //n是有效数组长度
    int t;
    printf("please enter the t: ");
    //t是空间
    scanf("%d",&t);
    printf("%5d\n",compute(n,t));
    return 0;
}
