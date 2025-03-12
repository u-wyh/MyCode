// 松鼠的新家(递归版)
// 有n个节点形成一棵树
// 给定一个由点编号组成的数组，表示松鼠依次要去往的地点
// 松鼠每走到一个节点都必须拿一个糖果，否则松鼠就停止前进
// 松鼠来到最后一个地点时不需要吃糖果
// 打印每个节点上至少准备多少糖果才能让松鼠依次走完数组里的节点
// 测试链接 : https://www.luogu.com.cn/problem/P3258
// 提交以下的code，提交时请把类名改成"Main"
// C++这么写能通过，java会因为递归层数太多而爆栈
// java能通过的写法参考本节课Code02_SquirrelHome2文件

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 300005;

int n;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int tcnt=1;
//建图的链式前向星

int headQuery[MAXN];
int queryNext[MAXN << 1];
int queryTo[MAXN << 1];
// 问题的编号，一旦有答案可以知道填写在哪
int queryIndex[MAXN << 1];
int qcnt=1;
//问题的链式前向星   包含一个问题的编号数组  用来填答案

// unionfind数组是tarjan算法专用的并查集结构
int unionfind[MAXN];
// father数组不用作并查集，就是记录每个节点的父亲节点
int father[MAXN];
// ans数组是tarjan算法的输出结果，记录每次旅行两端点的最低公共祖先
int ans[MAXN];
int travel[MAXN];
//表示一次经过的地点
bool visited[MAXN];
int num[MAXN];
//表示我们要输出的东西

void build(){
    for(int i=1;i<=n;i++){
        unionfind[i]=i;
    }
}
//并查集初始化

int find(int i) {
    if (i != unionfind[i]) {
        unionfind[i] = find(unionfind[i]);
    }
    return unionfind[i];
}

void tarjan(int u, int f) {
    visited[u] = true;
    for (int e = head[u], v; e != 0; e = Next[e]) {
        v = to[e];
        if (v != f) {
            tarjan(v, u);//向下递归  直到叶节点
        }
    }
    for (int e = headQuery[u], v; e != 0; e = queryNext[e]) {
        v = queryTo[e];
        if (visited[v]) {
            //如果说这个问题节点已经被访问过  才可以进行答案填写
            ans[queryIndex[e]] = find(v);
            //填写的答案是这个节点所在并查集的头结点
        }
    }
    unionfind[u] = f;
    father[u] = f;
}

void dfs(int u,int f){
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            dfs(v,u);
        }
    }
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            num[u]+=num[v];
        }
    }
}

void compute() {
    tarjan(1, 0);
    for (int i = 1, u, v, lca, lcafather; i < n; i++) {
        u = travel[i];
        v = travel[i + 1];
        lca = ans[i];
        lcafather = father[lca];
        num[u]++;
        num[v]++;
        num[lca]--;
        num[lcafather]--;
    }
    //目前实际上是完成了“差分”  还要组合一下
    dfs(1, 0);
    for (int i = 2; i <= n; i++) {
        num[travel[i]]--;
    }
}

int main()
{
    cin>>n;
    build();
    for(int i=1;i<=n;i++){
        cin>>travel[i];
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;

        Next[tcnt]=head[u];
        to[tcnt]=v;
        head[u]=tcnt++;

        Next[tcnt]=head[v];
        to[tcnt]=u;
        head[v]=tcnt++;

    }
    for(int i=1;i<n;i++){
        int u,v;
        u=travel[i];
        v=travel[i+1];

        queryNext[qcnt] = headQuery[u];
		queryTo[qcnt] = v;
		queryIndex[qcnt] = i;
		headQuery[u] = qcnt++;

        queryNext[qcnt] = headQuery[v];
		queryTo[qcnt] = u;
		queryIndex[qcnt] = i;
		headQuery[v] = qcnt++;
    }
    compute();
    for(int i=1;i<=n;i++){
        cout<<num[i]<<endl;
    }
    return 0;
}

