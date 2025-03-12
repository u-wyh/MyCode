//P2746
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;

vector<int>vec[MAXN];
int dfn[MAXN],low[MAXN];
int st[MAXN],top;
int color,Time;
int col[MAXN];
int in[MAXN],out[MAXN];
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
            //表示这个节点没有被访问过
            tarjan(v);
            low[x]=min(low[x],low[v]);
        }
        else if(instack[v]){
            //表示这个属于是回溯了 一定是同一个环上的
            low[x]=min(low[x],dfn[v]);
        }
    }
    if(dfn[x]==low[x]){
        col[x]=++color;
        //将所有节点按照颜色分类  完成缩点
        while(st[top]!=x){
            //属于同一个强联通分量
            col[st[top]]=color;
            instack[st[top]]=false;
            top--;
        }
        instack[x]=false;
        top--;
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        int v;
        cin>>v;
        while(v!=0){
            vec[i].push_back(v);
            cin>>v;
        }
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    //cout<<color<<endl;
    for(int i=1;i<=n;i++){
        for(int j=0;j<vec[i].size();j++){
            int v=vec[i][j];
            if(col[i]!=col[v]){
                in[col[v]]++;
                out[col[i]]++;
            }
        }
    }
    int ans1=0,ans2=0;
    for(int i=1;i<=color;i++){
        if(!in[i])
            ans1++;
        if(!out[i])
            ans2++;
    }
    cout<<ans1<<endl;
    if(color==1){
        cout<<0<<endl;
    }
    else{
        cout<<max(ans1,ans2)<<endl;
    }
    return 0;
}
