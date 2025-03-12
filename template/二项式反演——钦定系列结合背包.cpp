// 已经没有什么好害怕的了
// 给定两个长度为n的数组，a[i]表示第i个糖果的能量，b[i]表示第i个药片的能量
// 所有能量数值都不相同，每一个糖果要选一个药片进行配对
// 如果配对之后，糖果能量 > 药片能量，称为糖果大的配对
// 如果配对之后，糖果能量 < 药片能量，称为药片大的配对
// 希望做到，糖果大的配对数量 = 药片大的配对数量 + k
// 返回配对方法数，答案对 1000000009 取模
// 举例，a = [5, 35, 15, 45]，b = [40, 20, 10, 30]，k = 2，返回4，因为有4种配对方法
// (5-40，35-20，15-10，45-30)、(5-40，35-30，15-10，45-20)
// (5-20，35-30，15-10，45-40)、(5-30，35-20，15-10，45-40)
// 1 <= n <= 2000
// 0 <= k <= n
// 测试链接 : https://www.luogu.com.cn/problem/P4859
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 2001;
const int MOD = 1000000009;

int n, k;
int a[MAXN], b[MAXN];
long long fac[MAXN];
long long c[MAXN][MAXN];
long long small[MAXN];
long long dp[MAXN][MAXN];
long long g[MAXN];

// 预处理阶乘和组合数
void build() {
    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * i % MOD;
    }
    for (int i = 0; i <= n; i++) {
        c[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MOD;
        }
    }
}

// 计算配对方法数
long long compute() {
    build();
    sort(a + 1, a + n + 1);
    sort(b + 1, b + n + 1);
    for (int i = 1, cnt = 0; i <= n; i++) {
        while (cnt + 1 <= n && b[cnt + 1] < a[i]) {
            cnt++;
        }
        small[i] = cnt;
    }
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        dp[i][0] = dp[i - 1][0];
        for (int j = 1; j <= i; j++) {
            dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - 1] * (small[i] - j + 1) % MOD) % MOD;
        }
    }
    for (int i = 0; i <= n; i++) {
        g[i] = fac[n - i] * dp[n][i] % MOD;
    }
    long long ans = 0;
    for (int i = k; i <= n; i++) {
        if (((i - k) & 1) == 0) {
            ans = (ans + c[i][k] * g[i] % MOD) % MOD;
        } else {
            ans = (ans + c[i][k] * g[i] % MOD * (MOD - 1) % MOD) % MOD;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    if (((n + k) & 1) == 0) {
        k = (n + k) / 2;
        cout << compute() << endl;
    } else {
        cout << 0 << endl;
    }
    return 0;
}
