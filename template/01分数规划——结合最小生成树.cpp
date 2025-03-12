// 最优比率生成树
// 一共有n个村庄，每个村庄由(x, y, z)表示
// 其中(x,y)代表村庄在二维地图中的位置，z代表其海拔高度
// 任意两个村庄之间的距离就是二维地图中的欧式距离
// 任意两个村庄之间的修路花费就是海拔差值的绝对值
// 现在想把所有村庄连通起来，希望修路的条数尽量少，同时希望让
// 总花费 / 总距离，这个比值尽量小，返回最小的比值是多少，结果保留小数点后3位其余部分舍弃
// 2 <= n <= 10^3
// 0 <= x、y <= 10^4
// 0 <= z <= 10^7
// 测试链接 : http://poj.org/problem?id=2728
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1001;
const double sml = 1e-6;

int x[MAXN];
int y[MAXN];
int z[MAXN];
double dist[MAXN][MAXN];
double cost[MAXN][MAXN];
bool visit[MAXN];
double value[MAXN];
int n;

// 邻接矩阵结构下的prim算法，从节点1出发得到最小生成树的权值和
double prim(double x) {
    // 结余值做边权，进而统计距离
    // 距离只和边权有关，原始的dist、cost不重要
    // 从1号点出发，更新到所有点的距离，也就是value数组
    for (int i = 1; i <= n; i++) {
        visit[i] = false;
        value[i] = cost[1][i] - x * dist[1][i];
    }
    visit[1] = true;
    double sum = 0;
    // 最小生成树一定有n-1条边，所以一共有n-1轮解锁，每次解锁新的点进入最小生成树的点集
    for (int i = 1; i <= n - 1; i++) {
        // 在没有解锁的点中，找到离最小生成树的点集最近的点，进行解锁
        double minDist = INT_MAX;
        int next = 0;
        for (int j = 1; j <= n; j++) {
            if (!visit[j] && value[j] < minDist) {
                minDist = value[j];
                next = j;
            }
        }
        // 最小的边进入最小生成树的边集，解锁的点进入最小生成树的点集
        sum += minDist;
        visit[next] = true;
        // 查看新的解锁点能不能拉进其他点的距离
        for (int j = 1; j <= n; j++) {
            if (!visit[j] && value[j] > cost[next][j] - x * dist[next][j]) {
                value[j] = cost[next][j] - x * dist[next][j];
            }
        }
    }
    // 返回最小生成树的权值和
    return sum;
}

int main()
{
    cin>>n;
    while (n != 0) {
        for (int i = 1; i <= n; i++) {
            cin>>x[i]>>y[i]>>z[i];
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i != j) {
                    dist[i][j] = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
                    cost[i][j] = abs(z[i] - z[j]);
                }
            }
        }
        double l = 0, r = 100, x, ans = 0;
        while (l < r && r - l >= sml) {
            x = (l + r) / 2;
            // 如果最小生成树的权值 <= 0，达标，左侧二分找寻更小比值
            // 如果最小生成树的权值 > 0，不达标，右侧二分找寻更大比值
            if (prim(x) <= 0) {
                ans = x;
                r = x - sml;
            } else {
                l = x + sml;
            }
        }
        printf("%.3f\n", ans);
        cin>>n;
    }
    return 0;
}
