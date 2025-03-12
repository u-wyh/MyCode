#include<stdio.h>
#define Max 100

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int nums[Max];
    int i=0;
    while(scanf("%d",&nums[i++])==1);
    int n=i-1;
    int start[n];
    start[n - 1] = nums[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        // nums[i]
        // nums[i] + start[i+1]
        start[i] = max(nums[i], nums[i] + start[i + 1]);
    }
    int ans = start[0];
    // end : 子数组必须以i-1结尾，其中的最大累加和
    int end = nums[0];
    // maxEnd :
    // 0~i-1范围上，
    // 子数组必须以0结尾，其中的最大累加和
    // 子数组必须以1结尾，其中的最大累加和
		// ...
    // 子数组必须以i-1结尾，其中的最大累加和
    // 所有情况中，最大的那个累加和就是maxEnd
    int maxEnd = nums[0];
    for (int i = 1; i < n; i++) {
        // maxend   i....
        // 枚举划分点 i...
        ans = max(ans, maxEnd + start[i]);
        // 子数组必须以i结尾，其中的最大累加和
        end = max(nums[i], end + nums[i]);
        maxEnd = max(maxEnd, end);
    }
    ans = max(ans, maxEnd);
    printf("%5d\n",ans);
    return 0;
}
