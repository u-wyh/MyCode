#include<stdio.h>
#define Max 100

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int sum=0,nums[Max],i=0;
    while(scanf("%d",&nums[i])==1)
        sum+=nums[i++];
    int n=i;
    int dp[n+1][sum/2+1];
    for(i=0;i<=sum/2;i++)
        dp[0][i]=0;
    for(i=1;i<=n;i++)
    {
        for(int j=0;j<=sum/2;j++)
        {
            dp[i][j]=dp[i-1][j];
            if(j>=nums[i-1])
                dp[i][j]=max(dp[i-1][j],dp[i-1][j-nums[i-1]]+nums[i-1]);
        }
    }
    printf("%5d\n",sum-2*dp[n][sum/2]);
    return 0;
}
