//P3387
#include<bits/stdc++.h>
using namespace std;
const int MAXN =2e4+5;

vector<int>vec[MAXN];
vector<int>edge[MAXN];
int dfn[MAXN],low[MAXN];
int st[MAXN],top;
int color,Time;
int col[MAXN];
int in[MAXN],out[MAXN];
bool instack[MAXN];
int n,m;
int v[MAXN],val[MAXN];
int dp[MAXN];

void tarjan(int x){
    dfn[x]=++Time;
    low[x]=Time;
    st[++top]=x;
    instack[x]=true;
    for(int i=0;i<vec[x].size();i++){
        int v=vec[x][i];
        if(!dfn[v]){
            tarjan(v);
            low[x]=min(low[x],low[v]);
        }
        else if(instack[v]){
            low[x]=min(low[x],dfn[v]);
        }
    }
    if(dfn[x]==low[x]){
        col[x]=++color;
        val[color]+=v[x];
        while(st[top]!=x){
            col[st[top]]=color;
            val[color]+=v[st[top]];
            instack[st[top]]=false;
            top--;
        }
        instack[x]=false;
        top--;
    }
}

void dfs(int u){
    int ans=0;
    dp[u]=val[u];
    for(int i=0;i<edge[u].size();i++){
        int v=edge[u][i];
        if(dp[v]!=-1){
            ans=max(ans,dp[v]);
            continue;
        }
        dfs(v);
        ans=max(ans,dp[v]);
    }
    dp[u]+=ans;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>v[i];
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        vec[u].push_back(v);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<vec[i].size();j++){
            int v=vec[i][j];
            if(col[i]!=col[v]){
                in[col[v]]++;
                edge[col[i]].push_back(col[v]);
            }
        }
    }
    int ans=0;
    for (int i = 1; i <= color; ++i) {
        sort(edge[i].begin(), edge[i].end());
        auto last = unique(edge[i].begin(), edge[i].end());
        edge[i].erase(last, edge[i].end());
        dp[i]=-1;
    }
    for(int i=1;i<=color;i++){
        if(in[i]==0){
            dfs(i);
            ans=max(ans,dp[i]);
        }
    }
    cout<<ans<<endl;
    return 0;
}
