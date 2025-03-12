//P4315
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;

int n,m;
int val[MAXN];
struct node{
    int u,v;
}edge[MAXN];

//链式前向星建图
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int tot=1;

//线段树
int tree[MAXN<<2];
int lazy[MAXN<<2];
int change[MAXN<<2];
int len[MAXN<<2];//要记录长度 因为这里加的话是每一个元素都要加

//树链剖分部分
int son[MAXN];//重儿子编号  叶子结点没有
int id[MAXN];//重新编号后的编号
int rk[MAXN];//重新编号后的编号对应原来的编号是什么
int cnt;
int fa[MAXN];//父亲节点编号
int deep[MAXN];//节点深度
int sz[MAXN];//以该节点为首的子树节点总数
int top[MAXN];//这条重链的头结点

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

inline void addedge(int u,int v,int w){
    Next[tot]=head[u];
    to[tot]=v;
    weight[tot]=w;
    head[u]=tot++;
}

//第一遍dfs 完成sz、deep、fa、son数组的统计
void dfs1(int u,int f){
    fa[u]=f;
    deep[u]=deep[f]+1;
    sz[u]=1;
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        if(v==f){
            continue;
        }
        val[v]=weight[i];//这里变化
        dfs1(v,u);
        sz[u]+=sz[v];
        if(sz[son[u]]<sz[v]){
            son[u]=v;
        }
    }
    //cout<<u<<' '<<sz[u]<<endl;
}

//第二遍dfs 完成top、rk、id
void dfs2(int u,int t){
    top[u]=t;
    id[u]=++cnt;
    rk[cnt]=u;
    if(son[u]){
        //存在重儿子  优先遍历
        dfs2(son[u],t);
    }
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        if(v!=fa[u]&&v!=son[u]){
            dfs2(v,v);
            //另外在开一条重链
        }
    }
}

//线段树部分
void up(int i){
    tree[i]=max(tree[i<<1],tree[i<<1|1]);
}

//注意编号问题
void build(int l,int r,int i){
    lazy[i]=0;
    change[i]=-1;
    len[i]=r-l+1;
    if(l==r){
        tree[i]=val[rk[l]];
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void downlazy(int i,int v){
    tree[i]+=v;
    lazy[i]+=v;
}

void changelazy(int i,int v){
    tree[i]=v;
    lazy[i]=0;
    change[i]=v;
}

void down(int i){
    if(change[i]!=-1){
        changelazy(i<<1,change[i]);
        changelazy(i<<1|1,change[i]);
        change[i]=-1;
    }
    if(lazy[i]){
        downlazy(i<<1,lazy[i]);
        downlazy(i<<1|1,lazy[i]);
        lazy[i]=0;
    }
}

void add(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl>jobr){
        return ;
    }
    if(jobl<=l&&r<=jobr){
        downlazy(i,jobv);
    }
    else{
        int mid=(l+r)/2;
        down(i);
        if(jobl<=mid){
            add(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            add(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

void update(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl>jobr){
        return ;
    }
    if(jobl<=l&&r<=jobr){
        changelazy(i,jobv);
    }
    else{
        int mid=(l+r)/2;
        down(i);
        if(jobl<=mid){
            update(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            update(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl>jobr){
        return 0;
    }
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int mid=(l+r)/2;
        down(i);
        int ans=0;
        if(jobl<=mid){
            ans=max(ans,query(jobl,jobr,l,mid,i<<1));
        }
        if(jobr>mid){
            ans=max(ans,query(jobl,jobr,mid+1,r,i<<1|1));
        }
        return ans;
    }
}

inline void add(int x,int y,int val){
    while(top[x]!=top[y]){
        if(deep[top[x]]<deep[top[y]])
            swap(x,y);
        add(id[top[x]],id[x],val,1,n,1);//结算这条重链上存在的贡献
        x=fa[top[x]];
    }
    //两点在同一条重链上
    if(id[x]>id[y])
        swap(x,y);
    add(id[x]+1,id[y],val,1,n,1);
    //add(id[x],id[x],-val,1,n,1);//这里变化
    //结算贡献区间
}

inline void update(int x,int y,int val){
    while(top[x]!=top[y]){
        if(deep[top[x]]<deep[top[y]])
            swap(x,y);
        update(id[top[x]],id[x],val,1,n,1);//结算这条重链上存在的贡献
        //计算边权的时候  头结点也要变化  因为x变成头结点的父亲了
        x=fa[top[x]];
    }
    //两点在同一条重链上
    if(id[x]>id[y])
        swap(x,y);
    update(id[x]+1,id[y],val,1,n,1);
    //update(id[x],id[x],-val,1,n,1);//这里变化
    //结算贡献区间
}

inline int qmax(int x,int y){
    int ans=0;
    while(top[x]!=top[y]){
        if(deep[top[x]]<deep[top[y]])
            swap(x,y);
        ans=max(ans,query(id[top[x]],id[x],1,n,1));
        x=fa[top[x]];
    }
    if(id[x]>id[y])
        swap(x,y);
    ans=max(ans,query(id[x]+1,id[y],1,n,1));
    return ans;
}

signed main()
{
    n=read();
    for(int i=1;i<n;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedge(u,v,w);
        addedge(v,u,w);
        edge[i].u=u;
        edge[i].v=v;
    }
    dfs1(1,0);
    dfs2(1,1);
    build(1,n,1);
    string op;
    int u,v,w;
    cin>>op;
    while(op!="Stop"){
        if(op=="Max"){
            u=read(),v=read();
            cout<<qmax(u,v)<<endl;
        }
        else if(op=="Cover"){
            u=read(),v=read(),w=read();
            update(u,v,w);
        }
        else if(op=="Change"){
            u=read(),v=read();
            update(edge[u].u,edge[u].v,v);
        }
        else{
            u=read(),v=read(),w=read();
            add(u,v,w);
        }
        cin>>op;
    }
    return 0;
}
