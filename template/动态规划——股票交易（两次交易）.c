#include<stdio.h>
#include<limits.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int min(int a,int b)
{
    return a<b?a:b;
}

int maxprofit(int *nums,int n)
{
    int dp1[n+1];
    dp1[1]=0;
    int k=nums[1];
    for(int i=2;i<=n;i++)
    {
        k=min(k,nums[i]);
        dp1[i]=max(dp1[i-1],nums[i]-k);
    }
    int dp2[n+1];
    for(int i=1;i<=n;i++)
        dp2[i]=0;
    int ans=0;
    for(int i=2;i<=n;i++)
    {
        for(int j=1;j<=i;j++)
        {
            dp2[i]=max(dp2[i],dp1[j]+nums[i]-nums[j]);
        }
        ans=max(ans,dp2[i]);
    }
    return ans;
}

int maxprofit2(int *nums,int n)
{
    int dp1[n+1];
    dp1[1]=0;
    for (int i = 2, k = nums[1]; i <= n; i++) {
        k = min(k, nums[i]);
        dp1[i] = max(dp1[i - 1], nums[i] - k);
    }
    // best[i] : 0...i范围上，所有的dp1[i]-nums[i]，最大值是多少
    // 这是数组的设置完全是为了替代最后for循环的枚举行为
    int best [n+1];
    best[1] = dp1[1] - nums[1];
    for (int i = 2; i <= n; i++) {
        best[i] = max(best[i - 1], dp1[i] - nums[i]);
    }
    // dp2[i] : 0...i范围上发生两次交易，并且第二次交易在i时刻卖出，最大利润是多少
    int dp2 [n+1];
    int ans = 0;
    for (int i = 1; i < n; i++) {
        // 不需要枚举了
        // 因为，best[i]已经揭示了，0...i范围上，所有的dp1[i]-nums[i]，最大值是多少
        dp2[i] = best[i] + nums[i];
        ans = max(ans, dp2[i]);
    }
    return ans;
}
int maxprofit3(int* nums,int n) {
		int dp1  [n+1];
		int  best  [n+1];
		best[1] = -nums[1];
		int dp2 [n+1];
		int ans = 0;
		for (int i = 2, k = nums[1]; i <= n; i++) {
			k = min(k, nums[i]);
			dp1[i] = max(dp1[i - 1],nums[i] - k);
			best[i] =max(best[i - 1], dp1[i] - nums[i]);
			dp2[i] = best[i] + nums[i];
			ans = max(ans, dp2[i]);
		}
		return ans;
	}

	// 发现只需要有限几个变量滚动更新下去就可以了
	// 空间压缩的版本
	// 就是等义改写，不需要分析能力
int maxprofit4(int *nums,int n) {
    int dp1 = 0;
    int best = -nums[1];
    int ans = 0;
    for (int i = 2, k = nums[1]; i <=n; i++) {
        k = min(k, nums[i]);
        dp1 = max(dp1, nums[i] - k);
        best = max(best, dp1 - nums[i]);
        ans = max(ans, best + nums[i]); // ans = max(ans, dp2);
    }
    return ans;
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
    printf("%d\n",maxprofit(nums,n));
    printf("%d\n",maxprofit2(nums,n));
    printf("%d\n",maxprofit3(nums,n));
    printf("%d\n",maxprofit4(nums,n));
    return 0;
}
