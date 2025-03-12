// 牛场围栏
// 给定一个长度为n的数组arr, arr[i]代表第i种木棍的长度，每种木棍有无穷多个
// 给定一个正数m，表示你可以把任何一根木棍消去最多m的长度，同一种木棍可以消去不同的长度
// 你可以随意拼接木棍形成一个长度，返回不能拼出来的长度中，最大值是多少
// 如果你可以拼出所有的长度，返回-1
// 如果不能拼出来的长度有无穷多，返回-1
// 1 <= n <= 100
// 1 <= arr[i] <= 3000
// 1 <= m <= 3000
// 测试链接 : https://www.luogu.com.cn/problem/P2662
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 101;
const int MAXV = 3001;
const int MAXM = 30001;

int head[MAXV];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;

int n,m,x;
int arr[MAXN];
bool Set[MAXV];

auto compare = [](const pair<int, int>& left, const pair<int, int>& right) {
    return left.second > right.second; // 注意这里是大于，因为我们想要小根堆
};
priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> heap(compare);
//初始化建立小根堆
bool vis[MAXV];
int dis[MAXV];//记录这个组里面最早可以到达的点位置

void addEdge(int u, int v, int w) {
    Next[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

void dijkstra() {
    heap.push({ 0, 0 });
    dis[0] = 0;
    int u;
    int w;
    while (!heap.empty()) {
        u=heap.top().first;
        w=heap.top().second;
        heap.pop();
        if (vis[u]) {
            continue;
        }
        vis[u] = true;
        for (int ei = head[u], v; ei > 0; ei = Next[ei]) {
            v = to[ei];
            if (!vis[v] && dis[v] > w + weight[ei]) {
                dis[v] = w + weight[ei];
                heap.push({ v, dis[v] });
            }
        }
    }
}

int compute() {
    int ans = 0;
    if (x == 1) {
        ans = -1;
    } else {
        for (int i = 1; i <= n; i++) {
            for (int j = max(1, arr[i] - m); j <= arr[i]; j++) {
                if (!Set[j]) {
                    Set[j] = true;
                    for (int k = 0; k < x; k++) {
                        addEdge(k, (k + j) % x, j);
                    }
                }
            }
        }
        dijkstra();
        for (int i = 1; i < x; i++) {
            if (dis[i] == INT_MAX) {
                ans = -1;
                break;
            }
            ans = max(ans, dis[i] - x);
        }
    }
    return ans;
}

int main()
{
    cin>>n>>m;
    x = INT_MAX;
    for (int i = 1; i <= n; i++) {
        cin>>arr[i];
        x = min(x, max(1, arr[i] - m));
        //将最小的数字作为我们的基准数
    }
    for(int i=0;i<=x;i++){
        dis[i]=INT_MAX;
    }
    cout<<compute();
    return 0;
}
