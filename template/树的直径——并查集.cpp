// 造公园
// 一共n个节点，编号1~n，有m条边连接，边权都是1
// 所有节点可能形成多个连通区，每个连通区保证是树结构
// 有两种类型的操作
// 操作 1 x   : 返回x到离它最远的点的距离
// 操作 2 x y : 如果x和y已经连通，那么忽略
//              如果不连通，那么执行连通操作，把x和y各自的区域连通起来
//              并且要保证连通成的大区域的直径长度最小
// 测试链接 : https://www.luogu.com.cn/problem/P2195
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有用例

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 300005;

int n,m,q;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

// 并查集需要
int father[MAXN];
// 树型dp需要
// dist[u] : 从u开始必须往下走，能走出的最大距离，可以不选任何边
int dist[MAXN];
// diameter[i] : 如果i是集合的头节点，diameter[i]表示整个集合的直径长度
//               如果i不再是集合的头节点，diameter[i]的值没有用
// 并查集 + 集合打标签技巧，不会的看讲解056、讲解057
int diameter[MAXN];

int find(int i) {
    if (i != father[i]) {
        father[i] = find(father[i]);
    }
    return father[i];
}

// 树型dp的方式求直径长度
void dp(int u, int f) {
    for (int e = head[u], v; e != 0; e = Next[e]) {
        v = to[e];
        if (v != f) {
            dp(v, u);
        }
    }
    for (int e = head[u], v; e != 0; e = Next[e]) {
        v = to[e];
        if (v != f) {
            diameter[u] = max(diameter[u], max(diameter[v], dist[u] + dist[v] + 1));
            dist[u] = max(dist[u], dist[v] + 1);
        }
    }
}

int main()
{
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++){
        father[i]=i;
    }
    for (int i = 1, u, v; i <= m; i++) {
        cin>>u>>v;

        Next[cnt]=head[u];
        to[cnt]=v;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        head[v]=cnt++;

        u = find(u);
        v = find(v);
        //将各自变为各自集合的代表点
        father[u] = v;
        //合并不同集合  并打上相同标签
    }
    for (int i = 1; i <= n; i++) {
        if (i == father[i]) {
            dp(i, 0);
        }
        //如果这个点就是代表点 说明是一个新的集团
    }
    for (int i = 1, op, x, y; i <= q; i++) {
        cin>>op;
        if (op == 1) {
            cin>>x;
            x=find(x);
            cout<<diameter[x];
        } else {
            cin>>x>>y;
            x = find(x);
            y = find(y);
            if (x != y) {
                father[x] = y;
                diameter[y] = max((diameter[x] + 1) / 2 + (diameter[y] + 1) / 2 + 1,max(diameter[x], diameter[y]));
            }
        }
    }
    return 0;
}
