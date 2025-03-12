/*
这道题要求我们将一个有n个节点的多边形切割为n-2个三角形，且所有的线段不能相交，求所有三角形之积的最小值
我们的思路是定下两个点，在选取一个点就可以将所有的没有选择的分为两边
*/
#include<stdio.h>
#include<limits.h>
#define Max 100

static int dp[Max][Max];

int min(int a,int b)
{
    return a<b?a:b;
}

int f(int *nums, int l, int r) {
    if (dp[l][r] != -1) {
        return dp[l][r];
    }
    int ans = INT_MAX;
    if (l == r || l == r - 1) {
        ans = 0;
    } else {
        // l....r >=3
        // 0..1..2..3..4...5
        for (int m = l + 1; m < r; m++) {
            // l m r
            ans = min(ans, f(nums, l, m) + f(nums, m, r) + nums[l] * nums[m] * nums[r]);
        }
    }
    dp[l][r] = ans;
    return ans;
}

int minScoreTriangulation1(int* nums,int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = -1;
        }
    }
    return f(nums, 0, n - 1);
}

int main()
{
    int nums[Max];
    int i=0;
    while(scanf("%d",&nums[i++])==1);
    int n=i-1;
    printf("%d\n",minScoreTriangulation1(nums,n));
    return 0;
}
