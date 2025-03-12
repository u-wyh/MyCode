// 粉刷木板的最大收益
// 一共有n个木板，每个木板长度为1，最多粉刷一次，也可以不刷
// 一共有m个工人，每个工人用(li, pi, si)表示：
// 该工人必须刷连续区域的木板，并且连续的长度不超过li
// 该工人每刷一块木板可以得到pi的钱
// 该工人刷的连续区域必须包含si位置的木板
// 返回所有工人最多能获得多少钱
// 1 <= n <= 16000
// 1 <= m <= 100
// 1 <= pi <= 10000
// 测试链接 : http://poj.org/problem?id=1821
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有用例
#include<bits/stdc++.h>
using namespace std;

int n,m;
struct worker{
    int l,s,p;
}nums[105];
int dp[16000][105];
int q[105];
int l, r;

bool cmp(worker a,worker b){
    return a.s<b.s;
}

// 之前工人负责的区域以j号木板结尾时，返回指标的值
int value(int i, int pi, int j) {
	return dp[i - 1][j] - pi * j;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>nums[i].l>>nums[i].p>>nums[i].s;
    }
    sort(nums+1,nums+m+1,cmp);
    for (int i = 1, li, pi, si; i <= m; i++) {
        li = nums[i].l;
        pi = nums[i].p;
        si = nums[i].s;
        l = r = 0;
        for (int j = max(0, si - li); j < si; j++) {
            while (l < r && value(i, pi, q[r - 1]) <= value(i, pi, j)) {
                r--;
            }
            q[r++] = j;
        }
        for (int j = 1; j <= n; j++) {
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            if (j >= si) {
                if (l < r && q[l] == j - li - 1) {
                    l++;
                }
                if (l < r) {
                    dp[i][j] = max(dp[i][j], value(i, pi, q[l]) + pi * j);
                }
            }
        }
    }
    cout<<dp[m][n];
    return 0;
}
