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
int dist[MAXN];

void dp(int u,int f){
    for(int i=head[u];i>0;i=Next[i]){
        if(to[i]!=f){
            dp(to[i],u);
        }
    }
    //实际上是一个dfs
    for(int i=head[u];i>0;i=Next[i]){
        if(to[i]!=f){
            diameter=max(diameter,dist[u]+dist[to[i]]+weight[i]);
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
    cout<<diameter;
    return 0;
}

