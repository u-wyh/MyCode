// 扩展中国剩余定理模版
// 给出n个同余方程，求满足同余方程的最小正数解x
// 一共n个同余方程，x ≡ ri(% mi)
// 1 <= n <= 10^5
// 0 <= ri、mi <= 10^12
// 所有mi不一定互质
// 所有mi的最小公倍数 <= 10^18
// 测试链接 : https://www.luogu.com.cn/problem/P4777
// 测试链接 : https://www.luogu.com.cn/problem/P1495
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100001;

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

// 扩展中国剩余定理模版
// 可以用于解决模数不是互质的情况  适用范围更广
long long excrt(int n) {
    long long tail = 0, lcm = 1, tmp, b, c, x0;
    // ans = lcm * x + tail
    for (int i = 1; i <= n; i++) {
        // ans = m[i] * y + ri
        // lcm * x + m[i] * y = ri - tail
        // a = lcm
        // b = m[i]
        // c = ri - tail
        b = m[i];
        c = ((r[i] - tail) % b + b) % b;
        exgcd(lcm, b);
        if (c % d != 0) {
            return -1;
        }
        // ax + by = gcd(a,b)，特解是，x变量
        // ax + by = c，特解是，x变量 * (c/d)
        // ax + by = c，最小非负特解x0 = (x * (c/d)) % (b/d) 取非负余数
        // 通解 = x0 + (b/d) * n
        x0 = multiply(x, c / d, b / d);
        // ans = lcm * x + tail，带入通解
        // ans = lcm * (x0 + (b/d) * n) + tail
        // ans = lcm * (b/d) * n + lcm * x0 + tail
        // tail' = tail' % lcm'
        tmp = lcm * (b / d);
        tail = (tail + multiply(x0, lcm, tmp)) % tmp;
        lcm = tmp;
    }
    return tail;
}

int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>m[i]>>r[i];
    }
    cout<<excrt(n)<<endl;
    return 0;
}
