//P8435
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXM = 2e6+5;

int head[MAXN];
int Next[MAXM<<1];
int to[MAXM<<1];
int cnt=1;

int dfn[MAXN],low[MAXN];
int st[MAXN],top;
int color,Time;
int col[MAXN];
int n,m;
vector<int>ans[MAXN];

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

void addedge(int u,int v){
    Next[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void tarjan(int u,int f){
    dfn[u] = low[u] = ++Time;
	int child = 0;
	st[++top]=u;
	for (int i = head[u]; i ; i=Next[i]) {
		int v = to[i];
		if (!dfn[v]) {
            child++;
			tarjan(v, u);
			low[u] = min(low[u], low[v]);
			if (low[v] >= dfn[u] ){
                color++;
                while(st[top+1]!=v){
                    ans[color].push_back(st[top--]);
                }
                ans[color].push_back(u);
			}
		}
		else if(v!=f){
            low[u]=min(low[u],dfn[v]);
		}
	}
	if (f==0&&child==0)
        ans[++color].push_back(u);
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i,0);
        }
    }
    cout<<color<<endl;
    for(int i=1;i<=color;i++){
        cout<<ans[i].size()<<' ';
        for(int j=0;j<ans[i].size();j++){
            cout<<ans[i][j]<<' ';
        }
        cout<<endl;
    }
    return 0;
}
