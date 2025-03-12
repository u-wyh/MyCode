// 节点最多经过两次的tsp问题
// 给定有n个地点，用m条边无向边连接，每条边有权值
// 你可以任选一点出发，目标是经过所有的点，最终不必回到出发点
// 并且每个点最多可以到达两次
// 返回总路程最小是多少
// 1 <= n <= 10
// 1 <= m <= 100
// 测试链接 : https://acm.hdu.edu.cn/showproblem.php?pid=3001
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有用例
#include<iostream>
#include<cmath>
#include<climits>
using namespace std;
const int MAXN = 10;
const int MAXS = pow(3, MAXN);

int n,m;
int graph[MAXN][MAXN];
int dp[MAXN][MAXS];
int complete[1 << MAXN];//表示所有可能的最终有效状态
int size;

void dfs(int i, int bit, int s) {
    if (i == n) {
        complete[size++] = s;
    } else {
        dfs(i + 1, bit * 3, s + bit);//表示这个位置走了一次
        dfs(i + 1, bit * 3, s + 2 * bit);//表示这个位置走了两次
    }
}

void build() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = INT_MAX;
        }
    }
    int maxs = pow(3, n);
    for (int i = 0; i < n; i++) {
        for (int s = 0; s < maxs; s++) {
            dp[i][s] = -1;
        }
    }
    size = 0;
    dfs(0, 1, 0);
}

int f(int i, int s) {
    //表示最后一个到达的是i  不算这次到达i状态是s
    if (s == 0) {
        return 0;
    }
    if (dp[i][s] != -1) {
        return dp[i][s];
    }
    int ans = INT_MAX;
    for (int j = 0, bit = 1, pre; j < n; j++, bit *= 3) {
        if ((s / bit) % 3 > 0) {//枚举
            pre = f(j, s - bit);
            if (pre != INT_MAX && graph[j][i] != INT_MAX) {
                ans = min(ans, pre + graph[j][i]);
            }
        }
    }
    dp[i][s] = ans;
    return ans;
}

int compute() {
    int ans = INT_MAX;
    for (int k = 0; k < size; k++) {
        for (int i = 0, bit = 1; i < n; i++, bit *= 3) {
            ans = min(ans, f(i, complete[k] - bit));
            //依次枚举最后一个到达的点
        }
    }
    return ans;
}

int main()
{
    while(true){
        cin>>n>>m;
        build();
        for (int i = 1, u, v, w; i <= m; i++) {
            cin>>u>>v>>w;
            u-=1;
            v-=1;
            if (w < graph[u][v]) {
                graph[u][v] = graph[v][u] = w;//选择边权最小的建边
            }
        }
        int ans = compute();
        cout<<(ans == INT_MAX ? -1 : ans)<<endl;
    }
    return 0;
}
