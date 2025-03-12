// 种草的方法数(普通状压dp)
// 给定一个n*m的二维网格grid
// 网格里只有0、1两种值，0表示该田地不能种草，1表示该田地可以种草
// 种草的时候，任何两个种了草的田地不能相邻，相邻包括上、下、左、右四个方向
// 你可以随意决定种多少草，只要不破坏上面的规则即可
// 返回种草的方法数，答案对100000000取模
// 1 <= n, m <= 12
// 测试链接 : https://www.luogu.com.cn/problem/P1879
// 提交以下的code，提交时请把类名改成"Main"
// 普通状压dp的版本无法通过所有测试用例
// 有些测试样本会超时，这是dfs过程很费时导致的
#include <iostream>
#include <vector>
#include <cstring> // for memset

using namespace std;

const int MAXN = 12;
const int MAXM = 12;
const int MOD = 100000000;
const int MAXS = 1 << MAXM;

int grid[MAXN][MAXM];
int dp[MAXN][MAXS];
int n, m;

int f(int i, int s);

// 辅助函数：获取状态s中第j位的状态
int get(int s, int j) {
    return (s >> j) & 1;
}

// 辅助函数：设置状态s中第j位的状态为v，并返回新的状态
int set(int s, int j, int v) {
    return v == 0 ? (s & (~(1 << j))) : (s | (1 << j));
}

// 深度优先搜索函数
// 当前来到i行j列
// i-1行每列种草的状况s
// i行每列种草的状况ss
// 返回后续有几种方法
int dfs(int i, int j, int s, int ss) {
    if (j == m) {
        // 递归到下一行
        return f(i + 1, ss);
    }
    // 不种当前位置  直接递归到下一个位置
    int ans = dfs(i, j + 1, s, ss);
    // 如果可以种当前位置
    if (grid[i][j] == 1 && (j == 0 || !get(ss, j - 1)) && !get(s, j)) {
        // 种当前位置，并递归到下一个位置
        ans = (ans + dfs(i, j + 1, s, set(ss, j, 1))) % MOD;
    }
    return ans;
}

// 记忆化搜索函数
int f(int i, int s) {
    if (i == n) {
        return 1; // 所有行都处理完毕，返回1种方案（即成功）
    }
    if (dp[i][s] != -1) {
        return dp[i][s]; // 如果已经计算过，直接返回结果  记忆化搜索
    }
    int ans = dfs(i, 0, s, 0); // 从当前行的第0列开始搜索
    dp[i][s] = ans; // 记录结果
    return ans;
}

// 主计算函数
int compute() {
    memset(dp, -1, sizeof(dp)); // 初始化dp数组为-1
    return f(0, 0); // 从第0行、状态0开始搜索
}

int main() {
    // 输入
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    // 计算并输出结果
    cout << compute() << endl;
    return 0;
}
