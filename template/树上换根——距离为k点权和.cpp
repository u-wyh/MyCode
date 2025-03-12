// 每个节点距离k以内的权值和(递归版)
// 给定一棵n个点的树，每个点有点权
// 到达每个节点的距离不超过k的节点就有若干个
// 把这些节点权值加起来，就是该点不超过距离k的点权和
// 打印每个节点不超过距离k的点权和
// 注意k并不大
// 测试链接 : https://www.luogu.com.cn/problem/P3047
// 提交以下的code，提交时请把类名改成"Main"
// C++这么写能通过，java会因为递归层数太多而爆栈
// java能通过的写法参考本节课Code05_SumOfNearby2文件
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXK = 25;

int n,k;
int arr[MAXN];
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt=1;
int sum[MAXN][MAXK];
// sum[u][i] : 以u为头的子树内，距离为i的节点权值和
int dp[MAXN][MAXK];
// dp[u][i] : 以u做根，整棵树上，距离为i的节点权值和

void dfs1(int u,int f){
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            dfs1(v,u);
            for(int j=1;j<=k;j++){
                sum[u][j]+=sum[v][j-1];
            }
        }
    }
}

void dfs2(int u,int f){
    for (int e = head[u], v; e != 0; e = Next[e]) {
        v = to[e];
        if (v != f) {
            dp[v][0] = sum[v][0];
            dp[v][1] = sum[v][1] + dp[u][0];
            for (int i = 2; i <= k; i++) {
                dp[v][i] = sum[v][i] + dp[u][i - 1] - sum[v][i - 2];
            }
            dfs2(v, u);
        }
    }
}

int main()
{
    cin>>n>>k;
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;

        Next[cnt]=head[u];
        to[cnt]=v;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        head[v]=cnt++;
    }
    for(int i=1;i<=n;i++){
        cin>>sum[i][0];
    }
    dfs1(1,0);
    for(int i=0;i<=k;i++){
        dp[1][i]=sum[1][i];
    }
    dfs2(1,0);
    for (int i = 1, ans; i <= n; i++) {
        ans = 0;
        for (int j = 0; j <= k; j++) {
            ans += dp[i][j];
        }
        cout<<ans<<endl;
    }
    return 0;
}
