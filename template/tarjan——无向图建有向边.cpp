//P1407
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 8005;
const int MAXM = 24005;

int n,m;
map<string,int>graph;
int dfn[MAXN],low[MAXN];
int st[MAXN],top;
int color,Time;
int col[MAXN];
bool instack[MAXN];

int head[MAXN];
int Next[MAXM];
int to[MAXM];
int cnt=1;

void addedge(int u,int v){
    Next[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void tarjan(int x){
    dfn[x]=++Time;
    low[x]=Time;
    st[++top]=x;
    instack[x]=true;
    for(int i=head[x];i;i=Next[i]){
        int v=to[i];
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
        string girl,boy;
        cin>>girl>>boy;
        graph[girl]=i;
        graph[boy]=i+n;
        addedge(i,i+n);
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        string girl,boy;
        cin>>girl>>boy;
        addedge(graph[boy],graph[girl]);
    }
    for(int i=1;i<=2*n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    for(int i=1;i<=n;i++){
        if(col[i]==col[i+n]){
            cout<<"Unsafe"<<endl;
        }
        else{
            cout<<"Safe"<<endl;
        }
    }
    return 0;
}
