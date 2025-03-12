// 计算系数
// 多项式为，(ax + by)的k次方，其中a、b、k为常数
// 计算这个多项式展开后，x的n次方 * y的m次方，这一项的系数
// 0 <= k <= 1000
// 0 <= a、b <= 10^6
// n + m == k
// 测试链接 : https://www.luogu.com.cn/problem/P1313
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include<bits/stdc++.h>
using namespace std;
const int MOD = 10007;

long long fac[1005];
long long inv[1005];

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
    fac[0] = 1;
    for (int i = 1; i <= 1005; i++) {
        fac[i] = (fac[i - 1] * i) % MOD;
    }
    inv[1005] = power(fac[1005], MOD - 2);
    for (int i = 1004; i >= 0; i--) {
        inv[i] = (inv[i + 1] * (i + 1)) % MOD;
    }
}

// 组合公式
long long c(int n, int k) {
    return (((fac[n] * inv[k]) % MOD) * inv[n - k]) % MOD;
}


int main()
{
    int a,b,k,n,m;
    cin>>a>>b>>k>>n>>m;
    build();
    cout<<((((power(a, n) * power(b, m)) % MOD) * c(k, k - n)) % MOD)<<endl;
    return 0;
}
