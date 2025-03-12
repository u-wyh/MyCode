// 圆上连线
// 圆上有2n个点，这些点成对连接起来，形成n条线段，任意两条线段不能相交，返回连接的方法数
// 注意！答案不对 10^9 + 7 取模！而是对 10^8 + 7 取模！
// 1 <= n <= 2999
// 测试链接 : https://www.luogu.com.cn/problem/P1976
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include<bits/stdc++.h>
using namespace std;
const int MOD = 100000007;
const int MAXN = 1000001;

// 阶乘余数表
long long fac[MAXN];
// 阶乘逆元表
long long inv1[MAXN];
// 连续数逆元表
long long inv2[MAXN];

long long power(long long x, long long p) {
	long long ans = 1;
	while (p > 0) {
		if ((p & 1) == 1) {
			ans = (ans * x) % MOD;
		}
		x = (x * x) % MOD;
		p >>= 1;
	}
	return ans;
}

// 来自讲解099，题目3，生成阶乘余数表、阶乘逆元表
void build1(int n) {
	fac[0] = inv1[0] = 1;
	fac[1] = 1;
	for (int i = 2; i <= n; i++) {
		fac[i] = ((long long) i * fac[i - 1]) % MOD;
	}
	inv1[n] = power(fac[n], MOD - 2);
	for (int i = n - 1; i >= 1; i--) {
		inv1[i] = ((long long) (i + 1) * inv1[i + 1]) % MOD;
	}
}
	// 来自讲解099，题目2，生成连续数逆元表
void build2(int n) {
	inv2[1] = 1;
	for (int i = 2; i <= n + 1; i++) {
		inv2[i] = MOD - inv2[MOD % i] * (MOD / i) % MOD;
	}
}

long long c(int n, int k) {
	return (((fac[n] * inv1[k]) % MOD) * inv1[n - k]) % MOD;
}

// 公式1
long long compute1(int n) {
    build1(2 * n);
    return (c(2 * n, n) - c(2 * n, n - 1) + MOD) % MOD;
}

int main()
{
    int n;
    cin>>n;
    cout<<compute1(n)<<endl;
    return 0;
}
