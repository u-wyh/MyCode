// 到达首都的最少油耗
// 给你一棵 n 个节点的树（一个无向、连通、无环图）
// 每个节点表示一个城市，编号从 0 到 n - 1 ，且恰好有 n - 1 条路
// 0 是首都。给你一个二维整数数组 roads
// 其中 roads[i] = [ai, bi] ，表示城市 ai 和 bi 之间有一条 双向路
// 每个城市里有一个代表，他们都要去首都参加一个会议
// 每座城市里有一辆车。给你一个整数 seats 表示每辆车里面座位的数目
// 城市里的代表可以选择乘坐所在城市的车，或者乘坐其他城市的车
// 相邻城市之间一辆车的油耗是一升汽油
// 请你返回到达首都最少需要多少升汽油
// 测试链接 : https://leetcode.cn/problems/minimum-fuel-cost-to-report-to-the-capital/

#include<bits/stdc++.h>
using namespace std;
const int MAXN =100005;

vector<vector<int >>graph;
int sz[MAXN];
//表示到达当前位置时一共有多少人
int cost[MAXN];
//表示到达当前位置时一共花了多少油
int n,seats;
//n表示一共有n条路  seats表示座位数目

void f(int u, int p) {
    sz[u] = 1;
    for (int i=0;i<graph[u].size();i++) {
        int v=graph[u][i];
        if (v != p) {
            f(v,u);//向下递归
            sz[u] += sz[v];
            cost[u] += cost[v];
            // a/b向上取整，可以写成(a+b-1)/b
            // (size[v]+seats-1) / seats = size[v] / seats 向上取整
            cost[u] += (sz[v] + seats - 1) / seats;
            //这个地方加的是子节点到这个地方的油耗
        }
    }
}
//两个参数一个是当前节点  一个是他的父节点

int main()
{
    cin>>n>>seats;
    graph.resize(n+1);
    for(int i=1,u,v;i<=n;i++){
        cin>>u>>v;
        graph[u].push_back(v);
        graph[v].push_back(u);
        //在这里建立双向图，因为我们不知道哪个方向是对的
        //我们下面可以通过记录父节点来避免重复
        //不会有环  所以是对的
    }
    f(0,-1);//我们认为0的父节点是-1
    cout<<cost[0];
    return 0;
}
