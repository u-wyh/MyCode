// 表格填数
// 给定一个长度为n的数组arr，arr[i]表示i位置上方的正方形格子数量
// 那么从1位置到n位置，每个位置就是一个直方图，所有的直方图紧靠在一起
// 在这片区域中，你要放入k个相同数字，不能有任意两个数字在同一行或者同一列
// 注意在这片区域中，如果某一行中间断开了，使得两个数字无法在这一行连通，则不算违规
// 返回填入数字的方法数，答案对 1000000007 取模
// 1 <= n、k <= 500    0 <= arr[i] <= 10^6
// 测试链接 : https://www.luogu.com.cn/problem/P6453
// 因为本题给定的可用空间很少，所以数组为int类型，不用long类型
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1000000007;
const int MAXN = 501;
const int MAXH = 1000000;

// 所有数字
int arr[MAXN];
// 阶乘余数表
int fac[MAXH + 1];
// 阶乘逆元表
int inv[MAXH + 1];
// 笛卡尔树需要
int ls[MAXN];
int rs[MAXN];
int sta[MAXN];
// dfs需要
int size[MAXN];
// dp是动态规划表
int dp[MAXN][MAXN];
// tmp是动态规划的临时结果
int tmp[MAXN];
int n, k;

int power(int x, int p) {
    int ans = 1;
    while (p > 0) {
        if ((p & 1) == 1) {
            ans = (ans * x) % MOD;
        }
        x = (x * x) % MOD;
        p >>= 1;
    }
    return  ans;
}

int c(int n, int k) {
    return n < k ? 0 : ((long long) fac[n] * inv[k] % MOD * inv[n - k] % MOD);
}

void build() {
    fac[0] = fac[1] = inv[0] = 1;
    for (int i = 2; i <= MAXH; i++) {
        fac[i] = ( fac[i - 1] * i % MOD);
    }
    inv[MAXH] = power(fac[MAXH], MOD - 2);
    for (int i = MAXH - 1; i >= 1; i--) {
        inv[i] =  ( inv[i + 1] * (i + 1) % MOD);
    }
    for (int i = 1, top = 0, pos; i <= n; i++) {
        pos = top;
        while (pos > 0 && arr[sta[pos]] > arr[i]) {
            pos--;
        }
        if (pos > 0) {
            rs[sta[pos]] = i;
        }
        if (pos < top) {
            ls[i] = sta[pos + 1];
        }
        sta[++pos] = i;
        top = pos;
    }
}

void dfs(int u, int fa) {
    if (u == 0) {
        return;
    }
    dfs(ls[u], u);
    dfs(rs[u], u);
    size[u] = size[ls[u]] + size[rs[u]] + 1;
    for(int i=0;i<=k;i++){
        tmp[i]=0;
    }
    // 所有dfs过程都算上，这一部分的总复杂度O(n^2)
    for (int l = 0; l <= min(size[ls[u]], k); l++) {
        for (int r = 0; r <= min(size[rs[u]], k - l); r++) {
            tmp[l + r] = (int) (tmp[l + r] + (long) dp[ls[u]][l] * dp[rs[u]][r] % MOD) % MOD;
        }
    }
    // 所有dfs过程都算上，这一部分的总复杂度O(min(n的3次方, n * k平方))
    for (int i = 0; i <= min(size[u], k); i++) {
        for (int p = 0; p <= i; p++) {
            dp[u][i] = (int) (dp[u][i] + (long) c(size[u] - p, i - p) * c(arr[u] - arr[fa], i - p) % MOD
                    * fac[i - p] % MOD * tmp[p] % MOD) % MOD;
        }
    }
}

int compute() {
    build();
    dp[0][0] = 1;
    dfs(sta[1], 0);
    return dp[sta[1]][k];
}

signed main()
{
    cin>>n>>k;
    for (int i = 1; i <= n; i++) {
        cin>>arr[i];
    }
    cout<<compute()<<endl;
    return 0;
}
