// 树上点差分模版(递归版)
// 有n个节点形成一棵树，一开始所有点权都是0
// 给定很多操作，每个操作(a,b)表示从a到b路径上所有点的点权增加1
// 所有操作完成后，返回树上的最大点权
// 测试链接 : https://www.luogu.com.cn/problem/P3128
// 提交以下的code，提交时请把类名改成"Main"
// C++这么写能通过，java会因为递归层数太多而爆栈
// java能通过的写法参考本节课Code01_MaxFlow2文件
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 50005;
const int LIMIT = 16;

int n,m;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt=1;
int deep[MAXN],stjump[MAXN][LIMIT];
int power;
int num[MAXN];//记录点权

void dfs1(int u, int f) {
    deep[u] = deep[f] + 1;
    stjump[u][0] = f;
    for (int p = 1; p <= power; p++) {
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
    }
    //完成u的deep  stjump
    for (int e = head[u]; e != 0; e = Next[e]) {
        if (to[e] != f) {
            dfs1(to[e], u);
        }
        //向下递归
    }
}
//这个函数的作用是建立deep  st的信息

int lca(int a, int b) {
    if (deep[a] < deep[b]) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    //确定大小关系
    for (int p = power; p >= 0; p--) {
        if (deep[stjump[a][p]] >= deep[b]) {
            a = stjump[a][p];
        }
    }
    //首先将两者变为同一高度
    if (a == b) {
        return a;
    }
    //如果相同说明就是祖先关系
    for (int p = power; p >= 0; p--) {
        if (stjump[a][p] != stjump[b][p]) {
            a = stjump[a][p];
            b = stjump[b][p];
        }
        //判断跳完后是否符合规则
    }
    return stjump[a][0];
    //我们将头结点的祖先设置为0  实际上没有0
}

void dfs2(int u,int f){
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            dfs2(v,u);
        }
    }
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            num[u]+=num[v];
        }
    }
}
//更新修改后的信息

int main()
{
    cin>>n>>m;
    power=log2(n);
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;

        Next[cnt]=head[u];
        to[cnt]=v;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        head[v]=cnt++;

    }
    dfs1(1,0);
    for(int i=1;i<=m;i++){
        int u,v,lcafather,Lca;
        cin>>u>>v;
        Lca=lca(u,v);
        lcafather=stjump[Lca][0];
        num[u]++;
        num[v]++;
        num[Lca]--;
        num[lcafather]--;
    }
    dfs2(1,0);
    int maxans=0;
    for(int i=1;i<=n;i++){
        maxans=max(maxans,num[i]);
    }
    cout<<maxans;
    return 0;
}

