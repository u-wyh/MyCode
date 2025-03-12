//使用树形dp
// 树的直径模版(树型dp)
// 给定一棵树，边权可能为负，求直径长度
// 测试链接 : https://www.luogu.com.cn/problem/U81904
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有的用例
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 500005;

int n;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;

// 直径的开始点
int start;
// 直径的结束点
int en;
// 直径长度
int diameter;

// dist[u] : 从u开始必须往下走，能走出的最大距离，可以不选任何边
int dist[MAXN];
// ans[u] : 路径必须包含点u的情况下，最大路径和
int ans[MAXN];
//这两个数组的区别是  dist只能是一条边  ans可以使两条边
//dist是已经访问过的收益目前最大值
//dist一开始是0 表示什么都不选  ans也是
//dist[u]根据dist[v]+weight[i]更新为最大值
//ans通过dist[u]+dist[v]+weight[i]更新为最大值
//表示以前的最大边dist[u]  加上目前这条边的收益weight[i]   加上孩子节点的最大值  看看能否更新最大值
//实际上ans[u]可以理解为以u为首的子树可以形成的最大直径

void dp(int u,int f){
    for(int i=head[u];i>0;i=Next[i]){
        if(to[i]!=f){
            dp(to[i],u);
        }
    }
    //实际上是一个dfs
    for(int i=head[u];i>0;i=Next[i]){
        if(to[i]!=f){
            ans[u]=max(ans[u],dist[u]+dist[to[i]]+weight[i]);
            dist[u]=max(dist[u],dist[to[i]]+weight[i]);
        }
    }
}

int main()
{
    cin>>n;
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
    dp(1,0);
    for(int i=1;i<=n;i++){
        diameter=max(diameter,ans[i]);
    }
    cout<<diameter<<endl;
    return 0;
}


