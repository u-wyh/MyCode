// 墨墨的等式(dijkstra算法)
// 一共有n种正数，每种数可以选择任意个，个数不能是负数
// 那么一定有某些数值可以由这些数字累加得到
// 请问在[l...r]范围上，有多少个数能被累加得到
// 0 <= n <= 12
// 0 <= 数值范围 <= 5 * 10^5
// 1 <= l <= r <= 10^12
// 测试链接 : https://www.luogu.com.cn/problem/P2371
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXM = 5e6+5;

int n;
long l,r;
int x;
int head[MAXN];
int Next[MAXM];
int to[MAXM];
long weight[MAXM];
int cnt=1;
auto compare = [](const pair<int, long>& left, const pair<int, long>& right) {
    return left.second > right.second; // 注意这里是大于，因为我们想要小根堆
};
priority_queue<pair<int, long>, vector<pair<int, long>>, decltype(compare)> heap(compare);
//初始化建立小根堆
bool vis[MAXN];
long dis[MAXN];//记录这个组里面最早可以到达的点位置

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
    long w;
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

long compute(){
    dijkstra();
    long ans = 0;
    for (int i = 0; i < x; i++) {
        if (r >= dis[i]) {
            ans += (r - dis[i]) / x + 1;
        }
        if (l >= dis[i]) {
            ans -= (l - dis[i]) / x + 1;
        }
    }
    return ans;
}

int main()
{
    cin>>n>>l>>r;
    l--;
    cin>>x;
    for(int i=2,v;i<=n;i++){
        cin>>v;
        for (int j = 0; j < x; j++) {
            //每一个节点都要加一条边
            addEdge(j, (j + v) % x, v);
            //从余j组到余(j + v) % x组
        }
    }
    for(int i=0;i<x;i++){
        dis[i]=LONG_MAX;
    }
    cout<<compute();
    return 0;
}
