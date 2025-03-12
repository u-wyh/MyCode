//两次dfs
// 树的直径模版(两遍dfs)
// 给定一棵树，边权可能为负，求直径长度
// 测试链接 : https://www.luogu.com.cn/problem/U81904
// 提交以下的code，提交时请把类名改成"Main"
// 会有无法通过的用例，因为树上有负边
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
// dist[i] : 从规定的头节点出发，走到i的距离
int dist[MAXN];
// last[i] : 从规定的头节点出发，i节点的上一个节点
int last[MAXN];

void dfs(int u,int f,int w){
    last[u]=f;
    dist[u]=dist[f]+w;
    for(int i=head[u];i>0;i=Next[i]){
        if(to[i]!=f){
            dfs(to[i],u,weight[i]);
        }
    }
}

void road() {
    dfs(1, 0, 0);
    //这个起点是随机的  一般都是1
    start = 1;
    for (int i = 2; i <= n; i++) {
        if (dist[i] > dist[start]) {
            start = i;
        }
    }
    //选择离他距离最大的点  作为头结点
    //因为边权为正  所以对于任意节点而言  最远的点一定是直径端点中的一个
    dfs(start, 0, 0);
    en = 1;
    for (int i = 2; i <= n; i++) {
        if (dist[i] > dist[en]) {
            en = i;
        }
    }
    diameter = dist[en];
}
//两次调用dfs

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
    road();
    cout<<diameter;
    return 0;
}
