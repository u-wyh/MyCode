//P5852
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;

int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int dfn[MAXN];//dfn序
int rk[MAXN];//dfn序对应的原来序号
int low[MAXN];//表示以这个节点为头的子树dfn序最大是多少
int dfncnt;

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

void dfs(int u,int f){
    dfn[u]=++dfncnt;
    rk[dfncnt]=u;
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        if(v!=f){
            dfs(v,u);
        }
    }
    low[u]=dfncnt;
}

struct node{
    long long tree[MAXN];
    int lowbit(int x){
        return x&(-x);
    }
    void add(int x,int val){
        while(x<=n){
            tree[x]+=val;
            x+=lowbit(x);
        }
    }
    long long sum(int x){
        long long ans=0;
        while(x){
            ans+=tree[x];
            x-=lowbit(x);
        }
        return ans;
    }
}a,b;
//a树状数组维持的是在这个以i为首的子树上有多少种颜色是大家公共拥有的
//b树状数组维持的是如果头结点有一个颜色 那么整棵树上会增加多少效果

// 维护每个颜色的 dfn序集合
set<int> st[MAXN];

void update(int x,int val){
    a.add(dfn[x],val);
    a.add(low[x]+1,-val);//表示只在这个子树上增加d的颜色
    b.add(dfn[x],(low[x]-dfn[x]+1)*val);
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v),addedge(v,u);//建边
    }
    dfs(1,0);
    for(int i=1;i<=m;i++){
        int op,u;
        op=read(),u=read();
        if(op==1){
            int v=read();
            auto it = st[v].upper_bound(dfn[u]);
            // 检查是否有祖先已经被染色
            if (it != st[v].begin() && low[rk[*prev(it)]] >= low[u])
                continue;
            // 删除子树中已经被染色的节点
            while (it != st[v].end() && (*it) <= low[u]) {
                update(rk[*it], -1); // 撤销之前的更新
                st[v].erase(it++);
            }
            st[v].insert(dfn[u]); // 插入当前节点
            update(u, 1); // 更新树状数组
        }
        else{
            //ans首先加上这个子树上所有节点都有的颜色
            //b.sum(x)求的是所有dfn编号小于x的节点所有的贡献
            //b.sum(low[u]) - b.sum(dfn[u])  求得就是这颗子树上节点所包含的不是头结点所有的颜色
            long long ans=(low[u] - dfn[u] + 1) * a.sum(dfn[u]) + b.sum(low[u]) - b.sum(dfn[u]);
            cout<<ans<<endl;
        }
    }
    return 0;
}
