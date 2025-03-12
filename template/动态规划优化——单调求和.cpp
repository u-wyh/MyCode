// 不超过连续k个元素的最大累加和
// 给定一个长度为n的数组arr，你可以随意选择数字
// 要求选择的方案中，连续选择的个数不能超过k个
// 返回能得到的最大累加和
// 1 <= n、k <= 10^5
// 0 <= arr[i] <= 10^9
// 测试链接 : https://www.luogu.com.cn/problem/P2627
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有用例
#include<bits/stdc++.h>
using namespace std;

int n,k;
int arr[100005];
long sum[100005];
long q[100005];
long dp[100005];
int l,r;

// 不要i位置的数字产生的指标
long value(int i) {
	return i == 0 ? 0 : (dp[i - 1] - sum[i]);
}

int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + arr[i];
    }
    l = r = 0;
    q[r++] = 0;
    for (int i = 1; i <= n; i++) {
        while (l < r && value(q[r - 1]) <= value(i)) {
            r--;
        }
        q[r++] = i;
        if (l < r && q[l] == i - k - 1) {
            l++;
        }
        dp[i] = value(q[l]) + sum[i];
    }
    cout<<dp[n];
    return 0;
}
