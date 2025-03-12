// 摆放国王的方法数(轮廓线dp)
// 给定两个参数n和k，表示n*n的区域内要摆放k个国王
// 国王可以攻击临近的8个方向，所以摆放时不能让任何两个国王打架
// 返回摆放的方法数
// 1 <= n <= 9
// 1 <= k <= n*n
// 测试链接 : https://www.luogu.com.cn/problem/P1896
// 提交以下的code，提交时请把类名改成"Main"，有可能全部通过
// 不过更推荐写出空间压缩的版本
#include<iostream>
using namespace std;

int n,kings;
int dp[9][9][1<<9][2][82];

int get(int s, int j) {
	return (s >> j) & 1;
}

int set(int s, int j, int v) {
	return v == 0 ? (s & (~(1 << j))) : (s | (1 << j));
}


// 当前来到i行j列
// i-1行中，[j..m-1]列有没有摆放国王，用s[j..m-1]号格子表示
// i行中，[0..j-1]列有没有摆放国王，用s[0..j-1]号格子表示
// s表示轮廓线的状况
// (i-1, j-1)位置，也就是左上角，有没有摆放国王，用leftup表示
// 国王还剩下k个需要去摆放
// 返回有多少种摆放方法
long f(int i, int j, int s, int leftup, int k) {
	if (i == n) {
		return k == 0 ? 1 : 0;
	}
	if (j == n) {
		return f(i + 1, 0, s, 0, k);
	}
	if (dp[i][j][s][leftup][k] != -1) {
		return dp[i][j][s][leftup][k];
	}
	int left = j == 0 ? 0 : get(s, j - 1);
	int up = get(s, j);
	int rightup = get(s, j + 1);
	long ans = f(i, j + 1, set(s, j, 0), up, k);
	if (k > 0 && left == 0 && leftup == 0 && up == 0 && rightup == 0) {
		ans += f(i, j + 1, set(s, j, 1), up, k - 1);
	}
	dp[i][j][s][leftup][k] = ans;
	return ans;
}

int main()
{
    cin>>n>>kings;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int s = 0; s < (1<<n); s++) {
                for (int leftup = 0; leftup <= 1; leftup++) {
                    for (int k = 0; k <= kings; k++) {
                        dp[i][j][s][leftup][k] = -1;
                    }
                }
            }
        }
    }
    cout<<f(0, 0, 0, 0, kings);
    return 0;
}
