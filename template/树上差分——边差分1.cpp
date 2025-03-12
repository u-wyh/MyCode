// 边差分实战
// 使图不连通的方法数
// 有n个节点，给定n-1条老边使其连接成一棵树，再给定m条新边额外加在树上
// 你可以切断两条边让这个图不连通，切断的两条边必须是一条老边和一条新边
// 返回方法数
// 测试链接 : http://poj.org/problem?id=3417
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有用例
#include<iostream>
#include<cmath>
#include<cstdio>
using namespace std;
const int MAXN = 100001;
const int LIMIT = 17;

int power;
int n, m;
int num[MAXN];

int head[MAXN];
int Next[MAXN << 1];
int to[MAXN << 1];
int cnt=1;

int deep[MAXN];
int stjump[MAXN][LIMIT];

int ans;

//int log2(int n) {
//    int ans = 0;
//    while ((1 << ans) <= (n >> 1)) {
//        ans++;
//    }
//    return ans;
//}


void addedge(int u,int v){
    Next[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

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

void dfs2(int u, int f) {
    for (int e = head[u], v; e != 0; e = Next[e]) {
        v = to[e];
        if (v != f) {
            dfs2(v, u);
        }
    }
    for (int e = head[u], v, w; e != 0; e = Next[e]) {
        v = to[e];
        if (v != f) {
            w = 0 + num[v];
            if (w == 0) {
                ans += m;
            } else if (w == 1) {
                ans += 1;
            } else {
                ans += 0;
            }
            num[u] += num[v];
        }
    }
}

int main()
{
    scanf("%d %d",&n,&m);
    power=log2(n);
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        addedge(u,v);
        addedge(v,u);
    }
    dfs1(1,0);
    for(int i=1;i<=m;i++){
        int u,v,Lca;
        scanf("%d %d",&u,&v);
        Lca=lca(u,v);
        num[u]++,num[v]++;
        num[Lca]-=2;
    }
    dfs2(1,0);
    cout<<ans<<endl;
    return 0;
}
