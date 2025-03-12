// 中国剩余定理模版
// 给出n个同余方程，求满足同余方程的最小正数解x
// 一共n个同余方程，x ≡ ri(% mi)
// 1 <= n <= 10
// 0 <= ri、mi <= 10^5
// 所有mi一定互质
// 所有mi整体乘积 <= 10^18
// 测试链接 : https://www.luogu.com.cn/problem/P1495
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 11;

long long m[MAXN];
long long r[MAXN];

long long d, x, y, px, py;

// 原理来自，讲解033，位运算实现乘法
// a * b的过程自己实现，每一个中间过程都%mod
// 这么写目的是防止溢出，也叫龟速乘
long long multiply(long long a, long long b, long long mod) {
	// 既然是在%mod的意义下，那么a和b可以都转化成非负的
	// 本题不转化无所谓，但是其他题目可能需要转化
	// 尤其是b需要转化，否则while循环会跑不完
	a = (a % mod + mod) % mod;
	b = (b % mod + mod) % mod;
	long long ans = 0;
	while (b != 0) {
		if ((b & 1) != 0) {
			ans = (ans + a) % mod;
		}
		a = (a + a) % mod;
		b >>= 1;
	}
	return ans;
}

void exgcd(long long a, long long b) {
    if (b == 0) {
        d = a;
        x = 1;
        y = 0;
    } else {
        exgcd(b, a % b);
        px = x;
        py = y;
        x = py;
        y = px - py * (a / b);
    }
}

// 中国剩余定理模版  只适用于模数互质的情况
long long crt(int n) {
    long long lcm = 1;
    for (int i = 1; i <= n; i++) {
        lcm = lcm * m[i];
        //因为m是互质的  所以最小公倍数就是他们的累乘
    }
    long long ai, ci, ans = 0;
    for (int i = 1; i <= n; i++) {
        // ai = lcm / m[i]
        // 即 m1 * m2 *```* mi-1 * mi+1 *```* mn-1 * mn
        ai = lcm / m[i];
        // ai逆元，在%m[i]意义下的逆元
        exgcd(ai, m[i]);
        // ci = (ri *   ai * ai逆元(即x)  ) % lcm
        ci = multiply(r[i], multiply(ai, x, lcm), lcm);
        ans = (ans + ci) % lcm;
    }
    return ans;
}

int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>m[i]>>r[i];
    }
    cout<<crt(n)<<endl;
    return 0;
}
