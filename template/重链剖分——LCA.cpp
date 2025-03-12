//P8025
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;

int n,m,st;

//链式前向星建图
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int tot=1;

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

inline void addedge(int u,int v){
    Next[tot]=head[u];
    to[tot]=v;
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
        dfs1(v,u);
        sz[u]+=sz[v];
        if(sz[son[u]]<sz[v]){
            son[u]=v;
        }
    }
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

int lca;
int ans;

//函数作用是：判断x在limit步之内是否可以走到y
inline bool check(int x,int y,int limit){
    //cout<<x<<' '<<y<<' '<<id[x]<<' '<<id[y]<<' ';
    ans=0;
    while(top[x]!=top[y]){
        if(deep[top[x]]<deep[top[y]])
            swap(x,y);
        ans+=id[x]-id[top[x]]+1;
        //cout<<ans<<' ';
        x=fa[top[x]];
    }
    if(id[x]>id[y])
        swap(x,y);
    lca=id[x];
    ans+=id[y]-id[x];
    //cout<<"   "<<id[y]<<' '<<id[x]<<' '<<ans<<endl;
    return ans<=limit;
}

void sum(int u,int limit){
    if(check(st,u,limit)){
        st=u;
        return ;
    }
    //到了这里 说明无法在limit步以内走到u
    int father=lca;
    if(!check(st,lca,limit)){
        u=father;
    }
    else{
        limit=limit-ans;
        check(u,father,limit);//为了得到距离
        st=u;
        u=father;
        limit=ans-limit;
    }
    //那么这里要做的就是从st到u走limit步会到哪里  st比u低
    //并且此时u是st的祖先
    int tmp=0;
    while(top[st]!=top[father]){
        if(tmp+(id[st]-id[top[st]]+1)<=limit){
            tmp+=(id[st]-id[top[st]]+1);
            st=fa[top[st]];
        }
        else{
            break;
        }
    }
    tmp=id[st]-(limit-tmp);
    st=rk[tmp];
}

signed main()
{
    n=read(),st=read(),m=read();
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    dfs1(1,0);
    dfs2(1,1);
    for(int i=1;i<=m;i++){
        int u,limit;
        u=read(),limit=read();
        if(limit==0){
            cout<<st<<' ';
            continue;
        }
        sum(u,limit);
        //cout<<st<<' '<<endl;
        cout<<st<<' ';
    }
    return 0;
}

/*
3 1 2
1 2 2 3
3 4 1 1

8 1 5
1 2 2 3 3 4 1 5 5 6 6 7 7 8
4 5
7 5
1 1
2 2
8 4
*/
