#include<stdio.h>
#include<stdlib.h>

int cmp(const void *a,const void *b)
{
    return (*(int *)a-*(int *)b);
}

int min(int a,int b)
{
    return a<b?a:b;
}


int minCost(int *nums,int *dp,int n)
{
    if (n >= 1) {
        dp[1] = nums[1];
    }
    if (n >= 2) {
        dp[2] = nums[2];
    }
    if (n >= 3) {
        dp[3] = nums[3] + nums[1] + nums[2];
    }
    for (int i = 4; i <= n; i++) {
        dp[i] = min(dp[i - 1] + nums[i] + nums[1] , dp[i - 2] + 2 * nums[2] + nums[i] + nums[1]) ;
    }
    return dp[n];
}

int main()
{
    int n;
    scanf("%d",&n);
    int nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
    }
    qsort(nums+1,n,sizeof(int),cmp);
    int dp[n+1];
    printf("%d\n",minCost(nums,dp,n));
    return 0;
}
