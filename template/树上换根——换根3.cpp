// 翻转道路数量最少的首都
// 给定一棵n个点的树，但是给定的每条边都是有向的
// 需要选择某个城市为首都，要求首都一定可以去往任何一个城市
// 这样一来，可能需要翻转一些边的方向才能做到，现在想翻转道路的数量尽量少
// 打印最少翻转几条道路就可以拥有首都
// 如果有若干点做首都时，翻转道路的数量都是最少的，那么打印这些点
// 测试链接 : https://www.luogu.com.cn/problem/CF219D
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有用例

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;
int dp[MAXN];

void dfs1(int u,int f){
    dp[u]=0;
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            dfs1(v,u);
            dp[u]+=dp[v];
            if(weight[i]==0){
                dp[u]++;
            }
        }
    }
    //cout<<u<<"    "<<dp[u]<<endl;
}

void dfs2(int u,int f){
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            if(weight[i]==0){
                dp[v]=dp[u]-1;
            }else{
                dp[v]=dp[u]+1;
            }
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
        weight[cnt]=1;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        weight[cnt]=0;
        head[v]=cnt++;
    }
    dfs1(1,0);
    dfs2(1,0);
    int ans[MAXN],minans=INT_MAX,k=1;
    for(int i=1;i<=n;i++){
        if(dp[i]<minans){
            minans=dp[i];
            k=1;
            ans[k++]=i;
        }else if(dp[i]==minans){
            ans[k++]=i;
        }
    }
    cout<<minans<<endl;
    for(int i=1;i<k;i++){
        cout<<ans[i]<<' ';
    }
    return 0;
}
