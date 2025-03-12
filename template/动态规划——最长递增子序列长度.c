#include<stdio.h>
#define Max 100

//优化后的版本


// "最长递增子序列"使用如下二分搜索 :
// ends[0...len-1]是严格升序的，找到>=num的最左位置
// 如果不存在返回-1
//优化的效果主要体现在在原来我们需要找一个max  而现在只需要统计ends的个数就好了
int bs1(int* ends, int len, int num) {
    int l = 0, r = len - 1, m, ans = -1;
    while (l <= r) {
        m = (l + r) / 2;
        if (ends[m] >= num) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    return ans;
}
int lengthOfLIS2(int* nums,int n) {
    int ends [n];
    // len表示ends数组目前的有效区长度
    // ends[0...len-1]是有效区，有效区内的数字一定严格升序
    int len = 0;
    for (int i = 0, find; i < n; i++) {
        find = bs1(ends, len, nums[i]);
        if (find == -1) {
            ends[len++] = nums[i];
        } else {
            ends[find] = nums[i];
            //表示在长度为find的情况下  最后一个结尾是nums[i]是目前最优的（最小的）
            //因为最后一个值越小，那么后面可以加的东西就可能会越多 实现优化效果
        }
    }
    return len;
}

int main()
{
    int nums[Max];
    int i=0;
    while(scanf("%d",&nums[i++])==1);
    int n=i-1;
    printf("%5d\n",lengthOfLIS2(nums,n));
    return 0;
}

/*  暴力算法
int main()
{
    int nums[Max];
    int i=0;
    while(scanf("%d",&nums[i++])==1);
    int n=i-1;
    int dp[n];
    dp[0]=1;
    int max=1;
    for(i=1;i<n;i++)
    {
        dp[i]=1;
        for(int j=0;j<i;j++)
        {
            if(nums[j]<nums[i])
                dp[i]=dp[i]>(1+dp[j])?dp[i]:(1+dp[j]);
        }
        if(max<dp[i])
            max=dp[i];
    }
    printf("%5d\n",max);
    return 0;
}
*/
