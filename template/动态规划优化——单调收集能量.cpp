// 向下收集获得最大能量
// 有一个n * m的区域，行和列的编号从1开始
// 每个能量点用(i, j, v)表示，i行j列上有价值为v的能量点
// 一共有k个能量点，并且所有能量点一定在不同的位置
// 一开始可以在第1行的任意位置，然后每一步必须向下移动
// 向下去往哪个格子是一个范围，如果当前在(i, j)位置
// 那么往下可以选择(i+1, j-t)...(i+1, j+t)其中的一个格子
// 到达最后一行时，收集过程停止，返回能收集到的最大能量价值
// 1 <= n、m、k、t <= 4000
// 1 <= v <= 100
// 测试链接 : https://www.luogu.com.cn/problem/P3800
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有用例
#include<bits/stdc++.h>
using namespace std;

int n,m,k,t;
int dp[4005][4005];
int q[4005];
int l,r;

void add(int i, int j) {
	if (j <= m) {
		while (l < r && dp[i][q[r - 1]] <= dp[i][j]) {
			r--;
		}
		q[r++] = j;
	}
}

void overdue(int t) {
	if (l < r && q[l] == t) {
		l++;
	}
}

int main()
{
    cin>>n>>m>>k>>t;
    for(int i=1;i<=k;i++){
        int u,v,w;
        cin>>u>>v>>w;
        dp[u][v]=w;
    }
    for (int i = 2; i <= n; i++) {
        l = r = 0;
        for (int j = 1; j <= t; j++) {
            add(i - 1, j);
        }
        for (int j = 1; j <= m; j++) {
            add(i - 1, j + t);
            overdue(j - t - 1);
            dp[i][j] += dp[i - 1][q[l]];
        }
    }
    int ans = INT_MIN;
    for (int j = 1; j <= m; j++) {
        ans = max(ans, dp[n][j]);
    }
    cout<<ans;
    return 0;
}
