// 最大深度和(递归版)
// 给定一棵n个点的树，找到一个节点，使得以这个节点为根时，到达所有节点的深度之和最大
// 如果有多个节点满足要求，返回节点编号最小的
// 测试链接 : https://www.luogu.com.cn/problem/P3478
// 提交以下的code，提交时请把类名改成"Main"
// C++这么写能通过，java会因为递归层数太多而爆栈
// java能通过的写法参考本节课Code01_MaximizeSumOfDeeps2文件

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1000001;

int n;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt=1;
int sz[MAXN];//以该节点为头结点的子树大小
long long sum[MAXN];//所有子树的节点到该点的距离总和
long long dp[MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}


void dfs1(int u,int f){
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            dfs1(v,u);
        }
    }
    sz[u]=1;
    sum[u]=0;
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            sz[u]+=sz[v];//大小等于子树大小之和加上1（本身）
            sum[u]+=(sum[v]+sz[v]);//这里我们可以理解为边权是1
        }
    }
}
//建立sz  sum数组信息

void dfs2(int u,int f){
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            dp[v]=dp[u]-sz[v]+(n-sz[v]);
            dfs2(v,u);
            //先完成v节点  然后才可以向下遍历
        }
    }
}
//实现换根功能

int main()
{
    n=read();
    for(int i=1,u,v;i<n;i++){
        u=read(),v=read();

        Next[cnt]=head[u];
        to[cnt]=v;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        head[v]=cnt++;
    }
    dfs1(1,0);
    dp[1]=sum[1];
    //一开始只有dp[1]有效  因为现在我们认为根节点是1
    dfs2(1,0);
    long long maxans=LLONG_MIN;
    int ans=0;
    for(int i=1;i<=n;i++){
        if(dp[i]>maxans){
            ans=i;
            maxans=dp[i];
        }
    }
    cout<<ans;
    return 0;
}
