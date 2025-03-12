// 有趣的数列(重要! 因子计数法)
// 求第n项卡特兰数，要求答案对p取模
// 1 <= n <= 10^6
// 1 <= p <= 10^9
// p可能不为质数
// 测试链接 : https://www.luogu.com.cn/problem/P3200
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2000001;

// 如果minpf[i] == 0，代表i是质数
// 如果minpf[i] != 0，代表i是合数，并且最小质因子是minpf[i]
int minpf[MAXN];
// 质数表
int prime[MAXN];
// 质数表大小
int cnt;
// 因子计数
int counts[MAXN];

// 来自讲解097，欧拉筛，时间复杂度O(n)
void euler(int n) {
    for(int i=2;i<n;i++){
        minpf[i]=0;
    }
    cnt = 0;
    for (int i = 2; i <= n; i++) {
        // minpf[i] == 0代表i为质数，收集进质数表
        // minpf数组替代了讲解097中visit数组的作用
        if (minpf[i] == 0) {
            prime[cnt++] = i;
        }
        for (int j = 0; j < cnt; j++) {
            if (i * prime[j] > n) {
                break;
            }
            // 此时收集(i * prime[j])这个数的最小质因子为prime[j]
            // minpf[i * prime[j]] != 0，也标记了(i * prime[j])是合数
            // 讲解097欧拉筛的部分，重点解释了这个过程，看完必懂
            minpf[i * prime[j]] = prime[j];
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
}

long long power(long x, long p, int mod) {
    long ans = 1;
    while (p > 0) {
        if ((p & 1) == 1) {
            ans = (ans * x) % mod;
        }
        x = (x * x) % mod;
        p >>= 1;
    }
    return ans;
}

// 使用的是公式2 + 质因子计数法
int compute(int n, int mod) {
    // 利用欧拉筛生成[2 ~ 2*n]范围上所有数的最小质因子
    // 如果x为质数，minpf[x] == 0
    // 如果x为合数，x的最小质因子为minpf[x]
    euler(2 * n);
    // 分母每个因子设置计数
    for(int i=2;i<n+1;i++){
        counts[i]=-1;
    }
    // 分子每个因子设置计数
    for(int i=n+2;i<=2*n;i++){
        counts[i]=1;
    }
    // 从大到小的每个数统计计数
    // 合数根据最小质因子来分解，变成更小数字的计数
    // 质数无法分解，计数确定，最后快速幂计算乘积
    for (int i = 2 * n; i >= 2; i--) {
        if (minpf[i] != 0) {
            counts[minpf[i]] += counts[i];
            counts[i / minpf[i]] += counts[i];
            counts[i] = 0;
        }
    }
    // 每个质数的幂，都乘起来，就是最后答案
    long long ans = 1;
    for (int i = 2; i <= 2 * n; i++) {
        if (counts[i] != 0) {
			ans = ans * power(i, counts[i], mod) % mod;
        }
    }
    return (int) ans;
}

int main()
{
    int n;
    cin>>n;
    int mod;
    cin>>mod;
    cout<<compute(n,mod);
    return 0;
}
