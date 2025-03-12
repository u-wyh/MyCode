//P2863
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e4+5;

vector<int>vec[MAXN];
int dfn[MAXN],low[MAXN];
int st[MAXN],top;
int color,Time;
int sz[MAXN];
bool instack[MAXN];
int n,m;

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
        ++color;
        sz[color]++;
        while(st[top]!=x){
            sz[color]++;
            instack[st[top]]=false;
            top--;
        }
        instack[x]=false;
        top--;
    }
}

int main()
{
    cin>>n>>m;
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
    int ans=0;
    for(int i=1;i<=color;i++){
        //cout<<sz[color]<<' ';
        if(sz[i]>1)
            ans++;
    }
    cout<<ans<<endl;
    return 0;
}
