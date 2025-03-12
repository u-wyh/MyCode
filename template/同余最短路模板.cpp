// 跳楼机
// 一座大楼一共有h层，楼层编号1~h，有如下四种移动方式
// 1, 向上移动x层
// 2, 向上移动y层
// 3, 向上移动z层
// 4, 回到1层
// 假设你正在第1层，请问大楼里有多少楼层你可以到达
// 1 <= h <= 2^63 - 1
// 1 <= x、y、z <= 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P3403
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100001;
const int MAXM = 200001;
#define int long long

int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;

int x,y,z;
int h;

auto compare = [](const pair<int, int>& left, const pair<int, int>& right) {
    return left.second > right.second; // 注意这里是大于，因为我们想要小根堆
};
priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> heap(compare);
//初始化建立小根堆
bool vis[MAXN];
int dis[MAXN];//记录这个组里面最早可以到达的点位置

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

int compute(){
    dijkstra();
    int ans = 0;
    for (int i = 0; i < x; i++) {
        if (dis[i] <= h) {
            ans += (h - dis[i]) / x + 1;
        }
    }
    return ans;
}

signed main()
{
    cin>>h>>x>>y>>z;
    h-=1;
    for(int i=0;i<x;i++){
        dis[i]=LONG_MAX;
    }
    for (int i = 0; i < x; i++) {
        addEdge(i, (i + y) % x, y);
        addEdge(i, (i + z) % x, z);
        //单向图
    }
    //链式前向星建图
    cout<<compute();
    return 0;
}
