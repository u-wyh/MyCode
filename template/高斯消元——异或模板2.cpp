// 全变成1的最少操作次数
// 一共有n个点，m条无向边，每个点的初始状态都是0
// 可以操作任意一个点，操作后该点以及相邻点的状态都会改变
// 最终是希望所有点都变成1状态，那么可能会若干方案都可以做到
// 那么其中存在需要最少操作次数的方案，打印这个最少操作次数
// 题目保证一定能做到所有点都变成1状态，并且没有重边和自环
// 1 <= n <= 35
// 1 <= m <= 595
// 测试链接 : https://www.luogu.com.cn/problem/P2962
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 37;

int mat[MAXN][MAXN];
int op[MAXN];
int n,m,ans;

void prepare() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            mat[i][j] = 0;
        }
        mat[i][i] = 1;
        mat[i][n + 1] = 1;
        op[i] = 0;
    }
}

// 高斯消元解决异或方程组模版
// 需要保证变量有n个，表达式也有n个
void gauss(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j < i && mat[j][j] == 1) {
                continue;
            }
            if (mat[j][i] == 1) {
                swap(mat[i], mat[j]);
                break;
            }
        }
        if (mat[i][i] == 1) {
            for (int j = 1; j <= n; j++) {
                if (i != j && mat[j][i] == 1) {
                    for (int k = i; k <= n + 1; k++) {
                        mat[j][k] ^= mat[i][k];
                    }
                }
            }
        }
    }
}

void dfs(int i, int num) {
    if (num >= ans) { // 剪枝
        return;
    }
    if (i == 0) {
        ans = num;
    } else {
        if (mat[i][i] == 0) {
            // 当前是自由元
            // 自由元一定不依赖主元
            // 自由元也一定不依赖其他自由元
            // 所以当前自由元一定可以自行决定要不要操作
            op[i] = 0;
            dfs(i - 1, num);
            op[i] = 1;
            dfs(i - 1, num + 1);
        } else {
            // 当前是主元
            // 主元可能被其他自由元影响
            // 而且一定有，当前主元的编号 < 影响它的自由元编号
            // 所以会影响当前主元的自由元们，一定已经确定了要不要操作
            // 那么当前主元要不要操作，也就确定了
            //确定这个是主元之后  即使前面依旧存在自由元   但是绝不会影响这个主元的选择
            //能够影响当前主元的一定已经遍历过了
            int cur = mat[i][n + 1];
            for (int j = i + 1; j <= n; j++) {
                if (mat[i][j] == 1) {
                    cur ^= op[j];
                }
            }
            dfs(i - 1, num + cur);
        }
    }
}

int main()
{
    cin>>n>>m;
    prepare();
    for (int i = 1, u, v; i <= m; i++) {
        cin>>u>>v;
        mat[u][v] = 1;
        mat[v][u] = 1;
    }
    gauss(n);
    int sign = 1;
    for (int i = 1; i <= n; i++) {
        if (mat[i][i] == 0) {
            sign = 0;//表示存在自由元
            break;
        }
    }
    if (sign == 1) {
        // 唯一解  说明没有自由元
        // 那么需要调整的就只有值为1的点
        ans = 0;
        for (int i = 1; i <= n; i++) {
            if (mat[i][n + 1] == 1) {
                ans++;
            }
        }
    } else {
        // 多解
        ans = n;//最多只有n次
        dfs(n, 0);
    }
    cout<<ans<<endl;
    return 0;
}
