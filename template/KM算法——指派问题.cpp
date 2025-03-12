#include <bits/stdc++.h>
using namespace std;

// 定义一个非常大的数作为无穷大
const int INF = 1e9;

// 声明全局变量
int n; // 矩阵的大小（假设是方阵）
int cost[22][22]; // 成本矩阵
int matchX[22], matchY[22]; // 记录匹配关系
int lx[22], ly[22]; // 顶点的标号
bool visX[22], visY[22]; // 访问标记
int slack[22]; // 记录松弛量

// 深度优先搜索函数，用于寻找增广路径
bool dfs(int x) {
    visX[x] = true; // 标记X集合中的顶点x为已访问
    for (int y = 0; y < n; ++y) { // 遍历Y集合中的每个顶点y
        if (visY[y]) continue; // 如果y已经被访问过，则跳过
        int tmp = lx[x] + ly[y] - cost[x][y]; // 计算标号之和与边权之差
        if (tmp == 0) { // 如果找到一条可行边
            visY[y] = true; // 标记y为已访问
            // 如果y是未匹配点，或者可以从y的匹配点出发找到一条增广路径
            if (matchY[y] == -1 || dfs(matchY[y])) {
                matchX[x] = y; // 记录匹配关系
                matchY[y] = x;
                return true; // 找到增广路径，返回true
            }
        } else {
            // 如果不是可行边，则更新y的松弛量
            slack[y] = min(slack[y], tmp);
        }
    }
    return false; // 没有找到增广路径，返回false
}

// 更新顶点标号函数
void updateLabels() {
    int delta = INF;
    for (int y = 0; y < n; ++y) {
        if (!visY[y]) { // 对于所有未访问的Y集合中的顶点y
            delta = min(delta, slack[y]); // 找到最小的松弛量作为delta
        }
    }
    for (int x = 0; x < n; ++x) {
        if (visX[x]) lx[x] -= delta; // 更新X集合中已访问顶点的标号
    }
    for (int y = 0; y < n; ++y) {
        if (visY[y]) ly[y] += delta; // 更新Y集合中已访问顶点的标号
        else slack[y] -= delta; // 更新未访问顶点的松弛量
    }
    // 注意：这里不应该有对visX或visY的任何进一步引用或修改
    // 因为它们是在DFS过程中管理的，updateLabels函数只负责更新标号
}

// 匈牙利算法求解最小权重完美匹配
int hungarian() {
    memset(matchX, -1, sizeof(matchX)); // 初始化匹配关系为未匹配
    memset(matchY, -1, sizeof(matchY));
    memset(lx, 0, sizeof(lx)); // 初始化X集合顶点的标号为0
    memset(ly, 0, sizeof(ly)); // 初始化Y集合顶点的标号为0

    // 计算每个X集合顶点的初始标号lx[x]为与其相连的所有边的最大权重
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < n; ++y) {
            lx[x] = max(lx[x], cost[x][y]);
        }
    }

    // 对于每个X集合中的顶点x，尝试找到一条增广路径
    for (int x = 0; x < n; ++x) {
        fill(slack, slack + n, INF); // 初始化松弛量为无穷大
        while (true) { // 循环直到找到增广路径或无法再更新标号
            memset(visX, 0, sizeof(visX)); // 重置X集合顶点的访问标记
            memset(visY, 0, sizeof(visY)); // 重置Y集合顶点的访问标记
            if (dfs(x)) break; // 尝试寻找增广路径
            updateLabels(); // 更新顶点标号
        }
    }

    // 计算最小权重匹配的总权重
    int result = 0;
    for (int x = 0; x < n; ++x) {
        result += cost[x][matchX[x]]; // 累加每条匹配边的权重
    }
    return result; // 返回最小权重匹配的总权重
}

int main() {
    cin >> n; // 输入矩阵的大小
    vector<vector<int>> a(n, vector<int>(n)), b(n, vector<int>(n)); // 输入两个矩阵a和b
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j]; // 输入矩阵a的元素
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> b[i][j]; // 输入矩阵b的元素
        }
    }

    // 计算成本矩阵cost，其中cost[i][j] = a[i][j] * b[j][i]
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cost[i][j] = a[i][j] * b[j][i];
        }
    }

    // 调用匈牙利算法求解最小权重完美匹配
    int minCost = hungarian();
    cout << minCost << endl; // 输出最小权重匹配的总权重

    return 0;
}
