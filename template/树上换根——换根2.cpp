// 染色的最大收益
// 给定一棵n个点的树，初始时所有节点全是白点
// 第一次操作，你可以选择任意点染黑
// 以后每次操作，必须选择已经染黑的点的相邻点继续染黑，一直到所有的点都被染完
// 每次都获得，当前被染色点的白色连通块大小，作为收益
// 返回可获得的最大收益和
// 测试链接 : https://www.luogu.com.cn/problem/CF1187E
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有用例

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 200005;

int n;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt=1;
int sz[MAXN];//以该节点为头结点的子树大小
long long dp[MAXN];

// dp[i]更新成
// 节点i作为自己这棵子树最先染的点，染完子树后，收益是多少
void dfs1(int u,int f){
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            dfs1(v,u);
        }
    }
    sz[u]=1;
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            sz[u]+=sz[v];//大小等于子树大小之和加上1（本身）
            dp[u]+=dp[v];
        }
    }
    dp[u]+=sz[u];
}
//建立sz数组信息  在这个函数中我们只想要得到的是dp[1]即可

void dfs2(int u,int f){
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            dp[v]=dp[u]+n-sz[v]-sz[v];
            dfs2(v,u);
        }
    }
}

int main()
{
    cin>>n;
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;

        Next[cnt]=head[u];
        to[cnt]=v;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        head[v]=cnt++;
    }
    dfs1(1,0);
    dfs2(1,0);
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, dp[i]);
    }
    cout<<ans;
    return 0;
}
