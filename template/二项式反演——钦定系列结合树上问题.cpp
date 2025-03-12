// 游戏(递归版)
// 一共有n个节点，n <= 5000，n为偶数，其中有m个点属于小A，有m个点属于小B，m为n的一半
// 给定n-1条边，节点之间组成一颗树，1号节点是根节点
// 给定长度为n的数组arr，arr[i]的值表示i号节点由谁拥有，0为小A拥有，1为小B拥有
// 游戏有m回合，每回合都有胜负，两人需要选择一个自己拥有、但之前没选过的点，作为本回合当前点
// 小A当前点的子树里有小B当前点，则小A胜；小B当前点的子树里有小A当前点，则小B胜；否则平局
// 返回m回合里能出现k次非平局的游戏方法数，打印k=0..m时的所有答案，对 998244353 取模
// 两场游戏视为不同的定义：当且仅当存在小A拥有的点x，小B在小A选择x的那个回合所选择的点不同
// 测试链接 : https://www.luogu.com.cn/problem/P6478
// 提交以下的code，提交时请把类名改成"Main"，注意dfs是递归函数
// C++的同学可以全部通过，java的同学有时可以全部通过，有时因为递归展开太深而爆栈
// dfs从递归版改迭代版的实现，请看Code05_Game2文件
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MAXN = 5001;
const int MOD = 998244353;

int n, m;
int arr[MAXN];
long long fac[MAXN];
long long c[MAXN][MAXN];

// 链式前向星
int head[MAXN];
int next_[MAXN << 1];
int to[MAXN << 1];
int cnt;

// DFS 需要
int size[MAXN];
int belong[MAXN][2];
long long dp[MAXN][MAXN];
long long backup[MAXN];

// 反演需要
long long g[MAXN];

// 最后答案
long long f[MAXN];

void build() {
    cnt = 1;
    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
        head[i] = 0;
        fac[i] = fac[i - 1] * i % MOD;
    }
    for (int i = 0; i <= n; i++) {
        c[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MOD;
        }
    }
}

void addEdge(int u, int v) {
    next_[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

// 递归版 DFS
void dfs(int u, int fa) {
    size[u] = 1;
    belong[u][arr[u]] = 1;
    dp[u][0] = 1;
    // 首先计算不包含头节点的方法数
    for (int e = head[u]; e; e = next_[e]) {
        int v = to[e];
        if (v != fa) {
            dfs(v, u);
            // 之前所有子树结合的计算结果，拷贝进 backup
            for (int i = 0; i <= min(size[u] / 2, m); i++) {
                backup[i] = dp[u][i];
                dp[u][i] = 0;
            }
            // 树型 DP 的枚举行为利用子树的节点数做上限进行复杂度优化
            for (int l = 0; l <= min(size[u] / 2, m); l++) {
                for (int r = 0; r <= min(size[v] / 2, m - l); r++) {
                    dp[u][l + r] = (dp[u][l + r] + backup[l] * dp[v][r] % MOD) % MOD;
                }
            }
            size[u] += size[v];
            belong[u][0] += belong[v][0];
            belong[u][1] += belong[v][1];
        }
    }
    // 最后计算包含头节点的方法数
    // 更新 dp[u][i]，i 可以把上限定为 min(对手拥有的节点数，m)
    // u 为头的子树中，对手有几个节点
    int num = belong[u][arr[u] ^ 1];
    // 不包含头节点的方法数，拷贝到 backup
    for (int i = 1; i <= min(num, m); i++) {
        backup[i] = dp[u][i];
    }
    // 计算包含头节点的方法数，累加上
    for (int i = 1; i <= min(num, m); i++) {
        dp[u][i] = (dp[u][i] + backup[i - 1] * (num - i + 1) % MOD) % MOD;
    }
}

void compute() {
    dfs(1, 0); // DFS 是递归版
    for (int i = 0; i <= m; i++) {
        g[i] = dp[1][i] * fac[m - i] % MOD;
    }
    for (int k = 0; k <= m; k++) {
        for (int i = k; i <= m; i++) {
            if (((i - k) & 1) == 0) {
                f[k] = (f[k] + c[i][k] * g[i] % MOD) % MOD;
            } else {
                // -1 和 (MOD-1) 同余
                f[k] = (f[k] + c[i][k] * g[i] % MOD * (MOD - 1) % MOD) % MOD;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    m = n >> 1;
    build();
    string str;
    cin >> str;
    for (int i = 1; i <= n; i++) {
        arr[i] = str[i - 1] - '0';
    }
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    compute();
    for (int k = 0; k <= m; k++) {
        cout << f[k] << '\n';
    }
    return 0;
}
