// 参加会议II
// 给定n个会议，每个会议有开始时间、结束时间、收益三个值
// 参加会议就能得到收益，但是同一时间只能参加一个会议
// 一共能参加k个会议，如果选择参加某个会议，那么必须完整的参加完这个会议
// 会议结束日期是包含在会议内的，一个会议的结束时间等于另一个会议的开始时间，不能两个会议都参加
// 返回能得到的会议价值最大和
// 1 <= n * k <= 10^6
// 1 <= 开始时间、结束时间 <= 10^9
// 1 <= 收益 <= 10^6
// 测试链接 : https://leetcode.cn/problems/maximum-number-of-events-that-can-be-attended-ii/
#include<bits/stdc++.h>
using namespace std;

struct meeting{
    int st,en,val;
}nums[100005];
int n,k;

bool cmp(meeting a,meeting b){
    return a.en<b.en;
}

// 0...i范围上的会议，根据结束日期排序了
// 找到结束时间<s，最右的会议编号
// 如果不存在这样的会议返回-1
int find(int i, int s) {
	int l = 0, r = i, mid;
	int ans = -1;
	while (l <= r) {
		mid = (l + r) / 2;
		if (nums[mid].en < s) {
			ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return ans;
}

int main()
{
    cin>>n>>k;
    for(int i=0;i<n;i++){
        cin>>nums[i].st>>nums[i].en>>nums[i].val;
    }
    sort(nums,nums+n,cmp);
//    for(int i=0;i<n;i++){
//        cout<<nums[i].st<<' '<<nums[i].en<<' '<<nums[i].val<<endl;
//    }
    // dp[i][j] : 0..i范围上最多选j个会议召开，最大收益是多少
    vector<vector<int>> dp(n,vector<int>(k + 1, 0));
    for (int j = 1; j <= k; j++) {
        dp[0][j] = nums[0].val;//最多选j个  不是一定要选j个
    }
    for (int i = 1, pre; i < n; i++) {
        pre = find(i - 1, nums[i].st);
        for (int j = 1; j <= k; j++) {
            dp[i][j] = max(dp[i - 1][j], (pre == -1 ? 0 : dp[pre][j - 1]) + nums[i].val);
        }
    }
    cout<<dp[n-1][k]<<endl;
    return 0;
}
