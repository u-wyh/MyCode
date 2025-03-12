// 牛群聚集(递归版)
// 一共有n个节点，编号1~n，每个点有牛的数量
// 一共有n-1条边把所有点连通起来形成一棵树，每条边有权值
// 想把所有的牛汇聚在一点，希望走过的总距离最小
// 返回总距离最小是多少
// 利用重心的性质：
// 树上的边权如果都>=0，不管边权怎么分布，所有节点都走向重心的总距离和最小
// 测试链接 : https://www.luogu.com.cn/problem/P2986
// 提交以下的code，提交时请把类名改成"Main"
// C++这么写能通过，java会因为递归层数太多而爆栈
// java能通过的写法参考本节课Code03_GreatCowGathering2文件
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;

int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;
int cow[MAXN];
int n,cowSum=0;
int best=INT_MAX, center;
// size[i] : 从1号节点开始dfs的过程中，以i为头的子树，牛的总量
int sz[MAXN];
// path[i] : 从重心节点开始dfs的过程中，从重心到达i节点，距离是多少
int path[MAXN];

void setPath(int u, int f) {
    for (int e = head[u], v; e != 0; e = Next[e]) {
        v = to[e];
        if (v != f) {
            path[v] = path[u] + weight[e];
            setPath(v, u);
        }
    }
}
//确定path值

void findCenter(int u, int f) {
    sz[u] = cow[u];
    for (int e = head[u], v; e != 0; e = Next[e]) {
        v = to[e];
        if (v != f) {
            findCenter(v, u);
        }
    }
    // 如下代码是遍历完成后再做统计工作
    // 这个写法和之前的逻辑是一样的，为什么要拆开写？
    // 为了后续改迭代版方便
    int maxsub = 0;
    for (int e = head[u], v; e != 0; e = Next[e]) {
        v = to[e];
        if (v != f) {
            sz[u] += sz[v];
            maxsub = max(maxsub, sz[v]);
        }
    }
    maxsub = max(maxsub, cowSum - sz[u]);
    if (maxsub < best) {
        best = maxsub;
        center = u;
    }
}
//寻找重心操作

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>cow[i];
        cowSum+=cow[i];
    }
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;

        Next[cnt]=head[u];
        to[cnt]=v;
        weight[cnt]=w;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        weight[cnt]=w;
        head[v]=cnt++;
    }
    findCenter(1,0);
    //cout<<center<<endl;
    path[center] = 0;
    setPath(center, 0);
    long ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += (long) cow[i] * path[i];
    }
    cout<< ans;
    return 0;
}
//有边权和点权的图找重心   实际上边权没有什么作用
//只有点权可以有影响  体现在sz数组中
