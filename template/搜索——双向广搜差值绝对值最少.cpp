// 最接近目标值的子序列和
// 给你一个整数数组 nums 和一个目标值 goal
// 你需要从 nums 中选出一个子序列，使子序列元素总和最接近 goal
// 也就是说，如果子序列元素和为 sum ，你需要 最小化绝对差 abs(sum - goal)
// 返回 abs(sum - goal) 可能的 最小值
// 注意，数组的子序列是通过移除原始数组中的某些元素（可能全部或无）而形成的数组。
// 数据量描述:
// 1 <= nums.length <= 40
// -10^7 <= nums[i] <= 10^7
// -10^9 <= goal <= 10^9
// 测试链接 : https://leetcode.cn/problems/closest-subsequence-sum/

#include<bits/stdc++.h>
using namespace std;

int n,goal;
int nums[20];
int lsum[1<<10];
int rsum[1<<10];
int fi=0;

void collect(int* nums, int i, int e, int s, int* sum) {
    if (i == e) {
        sum[fi++] = s;
    } else {
        // nums[i.....]这一组，相同的数字有几个
        int j = i + 1;
        while (j < e && nums[j] == nums[i]) {
            j++;
        }
        // nums[ 1 1 1 1 1 2....
        //       i         j
        for (int k = 0; k <= j - i; k++) {
            // k = 0个
            // k = 1个
            // k = 2个
            collect(nums, j, e, s + k * nums[i], sum);
        }
    }
}

int main()
{
    cin>>n>>goal;
    for(int i=0;i<n;i++){
        cin>>nums[i];
    }
    long minans = 0;
    long maxans = 0;
    for (int i = 0; i < n; i++) {
        if (nums[i] >= 0) {
            maxans += nums[i];
        } else {
            minans += nums[i];
        }
    }
    //提前剪枝
    if (maxans < goal) {
        cout<< abs(maxans - goal);
        return 0;
    }
    if (minans > goal) {
        cout<< abs(minans - goal);
        return 0;
    }
    sort(nums,nums+n);//方便后期优化
    fi = 0;
    collect(nums, 0, n >> 1, 0, lsum);
    int lsize = fi;
    fi = 0;
    collect(nums, n >> 1, n, 0, rsum);
    int rsize = fi;
    sort(lsum,lsum+ lsize);
    sort(rsum,rsum+ rsize);
    int ans = abs(goal);
    for (int i = 0, j = rsize - 1; i < lsize; i++) {
        while (j > 0 && abs(goal - lsum[i] - rsum[j - 1]) <= abs(goal - lsum[i] - rsum[j])) {
            j--;
        }
        ans = min(ans, abs(goal - lsum[i] - rsum[j]));
    }
    cout<<ans;
    return 0;
}
