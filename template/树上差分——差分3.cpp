// 最小化旅行的价格总和(倍增方法求lca)
// 有n个节点形成一棵树，每个节点上有点权，再给定很多路径
// 每条路径有开始点和结束点，路径代价就是从开始点到结束点的点权和
// 所有路径的代价总和就是旅行的价格总和
// 你可以选择把某些点的点权减少一半，来降低旅行的价格总和
// 但是要求选择的点不能相邻
// 返回旅行的价格总和最少能是多少
// 测试链接 : https://leetcode.cn/problems/minimize-the-total-price-of-the-trips/

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100;
const int MAXM = 100;
const int LIMIT = 6;

int n,m;
//分别表示有多少个点  和多少条旅游路线
int price[MAXN];
//表示每一个点的点权
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt=1;
//链式前向星建图
int deep[MAXN],stjump[MAXN][LIMIT];
//倍增算法
int power;
int num[MAXN];
//记录经过该点的次数  一开始全都是0
int trip[MAXM][2];
//表示经过的路线顺序
int no,yes;
//no yes表示在不要当前头结点  或者 要当前头结点  最小消费
//其实可以用数组来存  当然空间浪费  没必要

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
//为了方便下面查询lca

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
//更新修改后的信息(次数信息)

void dp(int u,int f){
    int n=price[u]*num[u];//当前节点不优惠  这个节点上的花费
    int y=num[u]*(price[u]/2);//当前节点优惠  这个节点上的花费
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            dp(v,u);//向下递归
            n+=min(no,yes);
            y+=no;
        }
    }
    no=n;
    yes=y;
}
//树形dp

int main()
{
    cin>>n>>m;
    power=log2(n);
    for(int i=1;i<=n;i++){
        cin>>price[i];
    }
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
        cin>>trip[i][0]>>trip[i][1];
        int u,v;
        u=trip[i][0];
        v=trip[i][1];
        int lcafather,Lca;
        Lca=lca(u,v);
        lcafather=stjump[Lca][0];
        num[u]++;
        num[v]++;
        num[Lca]--;
        num[lcafather]--;
    }
    //完成差分信息准备
    dfs2(1,0);
    //填好所有信息
    dp(1,0);
    cout<<min(no,yes);
    return 0;
}

