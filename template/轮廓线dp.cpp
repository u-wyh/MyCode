// 种草的方法数(轮廓线dp)
// 给定一个n*m的二维网格grid
// 网格里只有0、1两种值，0表示该田地不能种草，1表示该田地可以种草
// 种草的时候，任何两个种了草的田地不能相邻，相邻包括上、下、左、右四个方向
// 你可以随意决定种多少草，只要不破坏上面的规则即可
// 返回种草的方法数，答案对100000000取模
// 1 <= n, m <= 12
// 测试链接 : https://www.luogu.com.cn/problem/P1879
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有用例
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MAXN = 12;
const int MAXM = 12;
const int MOD = 100000000;
const int MAXS = 1 << MAXM;

int grid[MAXN][MAXM];
int dp[MAXN][MAXM][MAXS];
int n, m;

// 辅助函数：获取状态s中第j位的状态
int get(int s, int j) {
    return (s >> j) & 1;
}

// 辅助函数：设置状态s中第j位的状态为v，并返回新的状态
int set(int s, int j, int v) {
    return v == 0 ? (s & (~(1 << j))) : (s | (1 << j));
}

// 当前来到i行j列
// i-1行中，[j..m-1]列的种草状况用s[j..m-1]表示
// i行中，[0..j-1]列的种草状况用s[0..j-1]表示
// s表示轮廓线的状况
// 返回后续有几种种草方法
int f(int i, int j, int s) {
	if (i == n) {
        //表示已经结束了
		return 1;
	}
	if (j == m) {
	    //表示换行
		return f(i + 1, 0, s);
	}
	if (dp[i][j][s] != -1) {
		return dp[i][j][s];
	}
	int ans = f(i, j + 1, set(s, j, 0));//这个位置选择0，并且必须要设置为0  否则就是上一行的这个数字
	if (grid[i][j] == 1 && (j == 0 || get(s, j - 1) == 0) && get(s, j) == 0) {
		ans = (ans + f(i, j + 1, set(s, j, 1))) % MOD;//表示这个位置选择1
	}
	dp[i][j][s] = ans;
	return ans;
}

int main()
{
    cin>>n>>m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int s = 0; s < (1<<m); s++) {
                dp[i][j][s] = -1;
            }
        }
    }
    cout<<f(0, 0, 0);
    return 0;
}
