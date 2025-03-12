// 炮兵阵地
// 给定一个n * m的二维数组grid，其中的1代表可以摆放炮兵，0代表不可以摆放
// 任何炮兵攻击范围是一个"十字型"的区域，具体是上下左右两个格子的区域
// 你的目的是在gird里摆尽量多的炮兵，但要保证任何两个炮兵之间无法互相攻击
// 返回最多能摆几个炮兵
// 1 <= n <= 100
// 1 <= m <= 10
// 0 <= grid[i][j] <= 1
// 测试链接 : https://www.luogu.com.cn/problem/P2704
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100;
const int MAXM = 10;
const int MAXS = 60;

int grid[MAXN][MAXM];
int dp[MAXN][MAXS][MAXS];
int sta[MAXS];
int n, m, k;

void prepare(int j, int s) {
    if (j >= m) {
        sta[k++] = s;
    } else {
        prepare(j + 1, s);
        prepare(j + 3, s | (1 << j));
    }
}

// 第i行士兵状态为s，结合grid第i号的状况
// 返回摆放士兵的数量
int onecnt(int i, int s) {
	int ans = 0;
	for (int j = 0; j < m; j++) {
		if (((s >> j) & 1) == 1 && grid[i][j] == 1) {
			ans++;
		}
	}
	return ans;
}

int main()
{
    cin>>n>>m;
    k=0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            cin>>c;
            grid[i][j] = c == 'H' ? 0 : 1;
        }
    }
    prepare(0,0);
    for (int a = 0, cnt; a < k; a++) {
        cnt = onecnt(0, sta[a]);
        dp[0][a][0] = cnt;
    }
    for (int i = 1; i < n; i++) {
        for (int a = 0, cnt; a < k; a++) {
            cnt = onecnt(i, sta[a]);
            for (int b = 0; b < k; b++) {
                if ((sta[a] & sta[b]) == 0) {
                    for (int c = 0; c < k; c++) {
                        if ((sta[b] & sta[c]) == 0 && (sta[a] & sta[c]) == 0) {
                            dp[i][a][b] = max(dp[i][a][b], dp[i - 1][b][c] + cnt);
                        }
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int a = 0; a < k; a++) {
        for (int b = 0; b < k; b++) {
            ans = max(ans, dp[n - 1][a][b]);
        }
    }
    cout<<ans;
    return 0;
}
