// 从上到下挖砖块(展示动态规划思路，不优化枚举，不进行空间压缩)
// 一堆组成倒三角形状的砖埋在地里，一共有n层，第1层有n块砖，每层递减，类似如下数据
// 4 2 9 5
//  3 1 7
//   2 4
//    8
// 需要从第1层开始挖，每挖开一块砖都可以获得数值作为收益，第1层的砖可以随意挖
// 但是挖到下面的砖是有条件的，想挖i层的j号砖，你需要确保i-1层的(j、j+1)块砖已经被挖开
// 最多可以挖m块砖，返回最大的收益
// 1 <= n <= 50
// 1 <= m <= 1300
// 砖块数值 <= 100
// 测试链接 : https://www.luogu.com.cn/problem/P1437
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 51;
const int MAXM = 1301;

int grid[MAXN][MAXN];
int dp[MAXN][MAXM];
int suffix[MAXN][MAXM];
int n, m;

// 预处理结构优化枚举
void prepare(int rowLimit) {
    for (int col = 0; col <= m; col++) {
        for (int row = rowLimit, suf = 0; row >= 0; row--) {
            suf = max(suf, dp[row][col]);
            suffix[row][col] = suf;
        }
    }
}

int main()
{
    cin>>n>>m;
    for (int j = 1; j <= n; j++) {
        for (int i = n; i >= j; i--) {
            cin>>grid[i][j];
        }
    }
    int ans = 0;
    for (int i = 1, cur, maxans; i <= n; i++) {
        prepare(i-1);
        // cur是当前行的收益
        cur = 0;
        for (int j = 0; j <= i; j++) {
            cur += grid[i][j];
            // 想挖到j号砖，总共挖的数量一定不少于
            // (j + 1) * j / 2，也就是等差数列
            // 如果k小于这个值无意义，认为收益是0
            for (int k = (j + 1) * j / 2; k <= m; k++) {
                dp[j][k] = suffix[max(0, j - 1)][k - j] + cur;
                ans = max(ans, dp[j][k]);
            }
        }
    }
    cout<<ans;
    return 0;
}
