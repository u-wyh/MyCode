//P9233
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int dfn[MAXN],id[MAXN];//dfn序  以及dfn对应的原来的序号
int dfncnt;
int sz[MAXN];
struct node{
    int l,r;
}q[MAXN];//改成n个区间查询
int qcnt;//记录区间查询编号
int n,m;
int cnt[MAXN];//统计元素出现个数
int tot[MAXN];//统计出现次数相同的个数
int ans;//记录出现次数的不同个数共有几个
int val[MAXN];
int pos[MAXN];

int head[MAXN];
int to[MAXN];
int Next[MAXN];
int tcnt=1;

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
    Next[tcnt]=head[u];
    to[tcnt]=v;
    head[u]=tcnt++;
}

void dfs(int u){
    dfn[u]=++dfncnt;
    id[dfncnt]=u;
    sz[u]=1;
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        dfs(v);
        sz[u]+=sz[v];
    }
    q[++qcnt]={dfn[u],dfn[u]+sz[u]-1};
}

//奇偶性排序优化
inline bool cmp(node a,node b) {
	return (pos[a.l] ^ pos[b.l]) ? pos[a.l] < pos[b.l] : ((pos[a.l] & 1) ? a.r < b.r : a.r > b.r);
}

void add(int x){
    if(cnt[val[x]]){
        //表示以前存在
        tot[cnt[val[x]]]--;//那么和这个出现次数相同的元素个数减少一个
        if(tot[cnt[val[x]]]==0){
            ans--;
            //如果减到0  那么种类减少一个
        }
    }
    cnt[val[x]]++;//出现次数加一
    tot[cnt[val[x]]]++;//这个出现次数的元素个数加一
    if(tot[cnt[val[x]]]==1){
        ans++;
        //表示以前没有这个出现次数 现在出现了
    }
}

void sub(int x){
    tot[cnt[val[x]]]--;//以前肯定有  要不然不会进入到这个函数
    if(tot[cnt[val[x]]]==0){
        ans--;
        //这个出现次数的没有了
    }
    cnt[val[x]]--;
    if(cnt[val[x]]!=0){
        //出现次数是0的话  不能统计
        tot[cnt[val[x]]]++;
        if(tot[cnt[val[x]]]==1){
            ans++;
        }
    }
}

int main()
{
    n=read();
    int size=sqrt(n);
    for(int i=1;i<=n;i++){
        pos[i]=i/size;
        val[i]=read();
        int u=read();
        addedge(u,i);
    }
    dfs(1);
    sort(q+1,q+n+1,cmp);
    int l=1,r=0,res=0;
    for(int i=1;i<=n;i++){
        while (l > q[i].l) add(id[--l]);
		while (r < q[i].r) add(id[++r]);
		while (l < q[i].l) sub(id[l++]);
		while (r > q[i].r) sub(id[r--]);
		res += (ans == 1);
    }
    cout<<res<<endl;
    return 0;
}
