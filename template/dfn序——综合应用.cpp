//P2982
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt=1;
int dfncnt=0;
int dfn[MAXN];
int size[MAXN];
int arr[MAXN];
int add[MAXN << 2];
int ans[MAXN<<2];

// 建树
void build(int l, int r, int i) {
    if (l == r) {
        ans[i] = 0;
    } else {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
    }
    add[i] = 0;
}

void addlazy(int i,int v){
    add[i] += v;
    ans[i] +=v;
}

// 懒信息的下发
void down(int i) {
    if (add[i] != 0) {
        // 发左
        addlazy(i << 1, add[i]);
        // 发右
        addlazy(i << 1 | 1, add[i]);
        // 父范围懒信息清空
        add[i] = 0;
    }
}

// 范围修改
// jobl ~ jobr范围上每个数字增加jobv
void Add(int jobl, int jobr, int jobv, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        addlazy(i, jobv);
    } else {
        int mid = (l + r) >> 1;
        down(i);
        if (jobl <= mid) {
            Add(jobl, jobr, jobv, l, mid, i << 1);
        }
        if (jobr > mid) {
            Add(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
    }
}

int query(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return ans[i];
    }
    int mid = (l + r) >> 1;
    down(i);
    int ans;
    if (jobl <= mid) {
        ans =query(jobl, jobr, l, mid, i << 1);
    }
    if (jobr > mid) {
        ans =query(jobl, jobr, mid + 1, r, i << 1 | 1);
    }
    return ans;
}

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
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

void dfs(int u){
    dfn[u]=++dfncnt;//dfn[]为树转换为dfs序中的下标
    size[u]=1;//u为根的子树大小
    int v;
    for(int i=head[u];i;i=Next[i]){
        v=to[i];
        if(dfn[v])continue;
        dfs(v);
        size[u]+=size[v];
    }
}

int main()
{
    cin>>n;
    for(int i=1,u,v;i<n;i++){
        u=read();
        v=read();
        addedge(u,v);
        addedge(v,u);
    }
    dfs(1);//使用dfn序
    build(1,n,1);
    for(int i=1,k;i<=n;i++){
        k=read();
        int ans=query(dfn[k],dfn[k],1,n,1);//单点查询
        Add(dfn[k],dfn[k]+size[k]-1,1,1,n,1);//每加入一个点后  以他为根的子树节点全部要加一
        //这样也就是每经过一次就要减慢一次
        cout<<ans<<endl;
    }
    return 0;
}
