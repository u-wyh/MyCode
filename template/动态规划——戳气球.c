/*
// 戳气球
// 有 n 个气球，编号为0到n-1，每个气球上都标有一个数字，这些数字存在数组nums中
// 现在要求你戳破所有的气球。戳破第 i 个气球
// 你可以获得 nums[i - 1] * nums[i] * nums[i + 1] 枚硬币
// 这里的 i - 1 和 i + 1 代表和 i 相邻的两个气球的序号
// 如果 i - 1或 i + 1 超出了数组的边界，那么就当它是一个数字为 1 的气球
// 求所能获得硬币的最大数量
// 测试链接 : https://leetcode.cn/problems/burst-balloons/
*/

#include<stdio.h>
#define Max 1000

static int dp[Max][Max];

int max(int a,int b)
{
    return a>b?a:b;
}

// nums[l...r]这些气球决定一个顺序，获得最大得分返回！
// 一定有 : nums[l-1]一定没爆！
// 一定有 : nums[r+1]一定没爆！
// 尝试每个气球最后打爆
int f(int* nums, int l, int r) {
    if (dp[l][r] != -1) {
        return dp[l][r];
    }
    int ans;
    if(l==r)
    {
        ans = nums[l - 1] *nums[l] * nums[r + 1];
    }
    else
    {
        // l   ....r
        // l +1 +2 .. r
        ans = max( nums[l - 1] * nums[l] * nums[r + 1] + f(nums, l + 1, r), // l位置的气球最后打爆
                   nums[l - 1] * nums[r] * nums[r + 1] + f(nums, l, r - 1));// r位置的气球最后打爆
        for(int k = l + 1; k < r; k++) {
            // k位置的气球最后打爆
            // l...k-1  k  k+1...r
            ans =max(ans, nums[l - 1] * nums[k] * nums[r + 1] + f(nums, l, k - 1) + f(nums, k + 1, r));
        }
    }
    dp[l][r] = ans;
    return ans;
}

int maxCoins1(int* nums,int n)
{
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            dp[i][j] = -1;
        }
    }
    return f(nums, 1, n);
}

int main()
{
    int n;
    scanf("%d",&n);
    int arr[n];
    int nums[n+2];
    nums[0]=1;
    nums[n+1]=1;
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
        nums[i+1]=arr[i];
    }
    printf("%d\n",maxCoins1(nums,n));
    return 0;
}
