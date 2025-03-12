//https://www.lanqiao.cn/problems/3506/learning/
//这道题十分的经典
//由于数据范围过大  暴力算法过不了
//所以我们使用了  倍增 最小生成树 lca 并查集 邻接表等算法辅助
//
//首先要建立一棵树  为了接下来的lca操作
//那么我们必须要排一下序  即最小生成树  根据题意可以确定排序方式
//除此之外 还要注意的是  可能得到的不是一棵树  即节点之间并不是一定联通的
//我们的fa数组仅仅是用来建立树的  除此之外 没有帮助也就是后面不会用到了
//当kruskal结束之后 我们的树也就建立好了
//边的信息存储在邻接表中
//
//准备两个st表
//st[i][j]用来存储节点i的第 2的j次方 的父亲节点是什么节点
//val[i][j]用来存储   节点i  到  (节点i 的第 2的j次方 的父亲节点)之间最小的值是什么(其他的题可能会用来存最大的值  这个根据题意 )
//
//deep数组用来存贮各个节点的深度 用于求lca
//vis数组是用于解决可能会有多棵树  所以判断一下这个节点有没有被树所包含 没有的话就要新建一棵树
//剩下的小细节全在代码里了
//
//为什么要这么做
//因为数据太大 我们需要使用倍增
//我们首先要得到他们父亲节点的信息  但是这仅仅是得到父亲节点的编号  这是不够的
//所以我们还要得到val数组
//那么即使如此  我们还是要建立一条从a到b的路径  这条路径可能是^  这种形状的  先上后下型的  有转折
//我们只有向上的父亲信息  没有向下的  这是不方便的  所以lca也就呼之欲出了

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 3e5+5;
const int LIMIT = 17;

int n,m,q;
struct node{
    int u,v,w;
}edge[MAXM];//一开始所有边的信息
int fa[MAXN];//用于建立树
bool vis[MAXN];
int st[MAXN][LIMIT+1];
int val[MAXN][LIMIT+1];//这里要注意如果是limit  那么下面代码中就不能访问val[i][limit] 越界了
int deep[MAXN];
vector<pair<int,int>>path[MAXN];

bool cmp(node a,node b){
    return a.w>b.w;
}
//将边排序

int find(int i){
    if (i != fa[i]){
        fa[i] = find(fa[i]);
    }
    return fa[i];
}

bool issame(int x,int y){
    return find(x)==find(y);
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        fa[fx]=fy;
    }
}
//以上三个程序都是为了生成树的并查集操作

void kruskal(){
    for(int i=1;i<=m;i++){
        int u=edge[i].u;
        int v=edge[i].v;
        int w=edge[i].w;
        if(!issame(u,v)){
            un(u,v);
            path[u].push_back({v,w});
            path[v].push_back({u,w});
        }
    }
}
//建立树

void dfs(int u,int f){
    vis[u]=true;
    st[u][0]=f;
    deep[u]=deep[f]+1;
    for(int i=1;i<=LIMIT;i++){
        //这个循环可以放在跑完子节点dfs之后  可能需要改变一点代码
        if(st[u][i-1]>0){
            st[u][i]=st[st[u][i-1]][i-1];
            val[u][i]=min(val[st[u][i-1]][i-1],val[u][i-1]);
        }
    }
    for(int i=0;i<path[u].size();i++){
        int v=path[u][i].first;
        int w=path[u][i].second;
        if(v!=f){
            val[v][0]=w;
            dfs(v,u);
        }
    }
}
//完成倍增表的信息填写

int lca(int a, int b) {
    int ans=INT_MAX;
    if (deep[a] < deep[b]) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    //确定大小关系  将a永远变为深度更深的点(与b相比)  这样仅仅是为了方便操作
    for (int p = LIMIT ;p >= 0; p--) {
        if (deep[st[a][p]] >= deep[b]) {
            ans=min(ans,val[a][p]);
            a = st[a][p];
            //注意这两行代码  不要换位置 不然a发生改变  得到的ans不是我们想要的
        }
    }
    //首先将两者变为同一高度
    if (a == b) {
        return ans;
    }
    //如果相同说明就是祖先关系  是祖先关系直接返回ans就可以了
    //如果不理解的话  仔细想想val这个倍增表的含义
    for (int p = LIMIT; p >= 0; p--) {
        if (st[a][p] != st[b][p]) {
            ans=min(ans,min(val[a][p],val[b][p]));
            a = st[a][p];
            b = st[b][p];
        }
        //判断跳完后是否符合规则
    }
    //跑到了这里  那么fa[a][0]和fa[b][0]是一样的  就是他们的祖先
    //不会的话建议学一下lca
    ans = min(ans,min(val[a][0],val[b][0]));
    return ans;
}

int main()
{
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=1;i<=m;i++){
        cin>>edge[i].u>>edge[i].v>>edge[i].w;
    }
    sort(edge+1,edge+m+1,cmp);
    kruskal();
    //建树
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            dfs(i,0);
        }
    }
    for(int i=1;i<=q;i++){
        int u,v;
        cin>>u>>v;
        if(find(u)!=find(v)){
            //如果不联通的话 直接返回-1
            cout<<-1<<endl;
        }
        else{
            cout<<lca(u,v)<<endl;
        }
    }
    return 0;
}
/*
5 4 3
1 2 5
2 3 6
3 4 1
4 5 10
1 4
3 4
1 3
*/
