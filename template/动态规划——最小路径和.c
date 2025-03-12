#include<stdio.h>

int main()
{
    int m,n;
    scanf("%d %d",&m,&n);
    int a[m][n],dp[m][n];
    int i,j;
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
    dp[0][0]=a[0][0];
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            if(i==0&&j==0) continue;
            else if(i==0)
                dp[i][j]=dp[i][j-1]+a[i][j];
            else if(j==0)
                dp[i][j]=dp[i-1][j]+a[i][j];
            else
            {
                if(dp[i][j-1]<=dp[i-1][j])
                    dp[i][j]=dp[i][j-1]+a[i][j];
                else //if(dp[i][j-1]>dp[i-1][j])
                    dp[i][j]=dp[i-1][j]+a[i][j];
            }
        }
    }
    printf("%d\n",dp[m-1][n-1]);
    return 0;
}
