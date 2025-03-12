// 摆盘子的方法
// 一共有n个盘子k种菜，所有盘子排成一排，每个盘子只能放一种菜
// 要求最多连续两个盘子菜品一样，更长的重复出现是不允许的
// 返回摆盘的方法数，答案对 1000000007 取模
// 1 <= n <= 1000
// 1 <= k <= 1000
// 来自真实大厂笔试，对数器验证
#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;

int n,k;

// 正式方法的尝试思路
int f1(int i) {
    if (i == 0) {
        return 1;
    }
    if (i == 1) {
        return k - 1;
    }
    long p1 = f1(i - 1);
    long p2 = f1(i - 2);
    return (int) (((p1 + p2) * (k - 1)) % MOD);
}

int dp1() {
    if (n == 1) {
        return k;
    }
    return (int) ((((long) f1(n - 1) + f1(n - 2)) * k) % MOD);
}

// 正式方法的普通动态规划版本
// 时间复杂度O(n)
int dp2() {
	if (n == 1) {
		return k;
	}
	int dp[n];
	dp[0] = 1;
	dp[1] = k - 1;
	for (int i = 2; i < n; i++) {
		long p1 = dp[i - 1];
		long p2 = dp[i - 2];
		dp[i] = (int) (((p1 + p2) * (k - 1)) % MOD);
	}
	return (int) ((((long) dp[n - 1] + dp[n - 2]) * k) % MOD);
}

// 最优解的版本，动态规划 + 矩阵快速幂优化
// 时间复杂度O(log n)
// 不会的同学看讲解098
typedef vector<vector<long long>> Matrix;

Matrix multiply(const Matrix& a, const Matrix& b) {
    int n = a.size();
    int m = b[0].size();
    int k = a[0].size();
    Matrix ans(n, vector<long long>(m, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int c = 0; c < k; ++c) {
                ans[i][j] = (ans[i][j] + a[i][c] * b[c][j]) % MOD;
            }
        }
    }
    return ans;
}

Matrix power(const Matrix& m, int p) {
    int n = m.size();
    Matrix ans(n, vector<long long>(n, 0));
    for (int i = 0; i < n; ++i) {
        ans[i][i] = 1;
    }
    Matrix base = m;
    while (p > 0) {
        if (p % 2 == 1) {
            ans = multiply(ans, base);
        }
        base = multiply(base, base);
        p /= 2;
    }
    return ans;
}

int dp3() {
    if (n == 1) {
        return k;
    }
    int s = k - 1;
    Matrix start = { {1, s} };
    Matrix base = { {0, s}, {1, s} };
    Matrix ans = multiply(start, power(base, n - 2));
    return ((ans[0][0] + ans[0][1]) * k) % MOD;
}

int main()
{
    cin>>n>>k;
    cout<<dp1()<<endl;
    cout<<dp2()<<endl;
    cout<<dp3()<<endl;
    return 0;
}
