// 集合计数
// 一共有n个不同的数，能构成2^n个不同集合
// 在2^n个集合中挑出若干个集合，至少挑一个
// 希望这若干个集合的交集，正好有k个数
// 返回挑选集合的方案数，答案对 1000000007 取模
// 1 <= n <= 10^6
// 0 <= k <= n
// 测试链接 : https://www.luogu.com.cn/problem/P10596
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;
const int MOD = 1e9+7;

long long fac[MAXN];
long long inv[MAXN];
long long g[MAXN];
int n,k;

// 快速幂计算 a^b % MOD
long long power(long long a, int b) {
    long long ans = 1;
    a = a % MOD;
    while (b > 0) {
        if (b & 1) {
            ans = (ans * a) % MOD;
        }
        a = (a * a) % MOD;
        b >>= 1;
    }
    return ans;
}

// 构建阶乘表和逆元表
void build() {
    fac[0] = inv[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = (fac[i - 1] * i) % MOD;
    }
    inv[n]=power(fac[n],MOD-2);
    for (int i = n-1; i >= 1; i--) {
        inv[i] = (inv[i + 1] * (i + 1)) % MOD;
    }
}

// 组合公式
long long c(int n, int k) {
    return (((fac[n] * inv[k]) % MOD) * inv[n - k]) % MOD;
}

long long compute() {
    build();
    long tmp = 2;
    for (int i = n; i >= 0; i--) {
        g[i] = tmp;
        tmp = tmp * tmp % MOD;
    }
    //第四种反演方法
    for (int i = 0; i <= n; i++) {
        // -1 和 (MOD-1) 同余
        g[i] = (g[i] + MOD - 1) * c(n, i) % MOD;
        //这个是基本项
    }
    long ans = 0;
    for (int i = k; i <= n; i++) {
        //由于i每次增加1  所以要mod-1
        if (((i - k) & 1) == 0) {
            ans = (ans + c(i, k) * g[i] % MOD) % MOD;
        } else {
            // -1 和 (MOD-1) 同余
            ans = (ans + c(i, k) * g[i] % MOD * (MOD - 1) % MOD) % MOD;
        }
    }
    return ans;
}

int main()
{
    cin>>n>>k;
    cout<<compute()<<endl;
    return 0;
}
