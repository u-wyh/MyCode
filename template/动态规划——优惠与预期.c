#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int compute(int n,int t,int *cost,int *val)
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
    int n,x;
    scanf("%d %d",&n,&x);
    int a[n],b[n],happy[n],well[n],ans=0,k=0;
    int cost[n],val[n];
    for(int i=0;i<n;i++)
    {
        scanf("%d %d %d",&a[i],&b[i],&happy[i]);
        well[i]=(a[i]-2*b[i]);
        if(well[i]>=0)
        {
            ans+=happy[i];
            x+=well[i];
        }
        else
        {
            cost[k]=-well[i];
            val[k]=happy[i];
            k++;
        }
    }
    printf("%d\n",ans+compute(k,x,cost,val));
    return 0;
}
