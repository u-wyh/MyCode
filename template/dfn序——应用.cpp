//P3605
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
struct node{
    int num,id,sub;
}arr[MAXN];
int dfncnt=0;
int dfn[MAXN];
int size[MAXN];
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt=1;
int tree[MAXN];
int ans[MAXN];

bool cmp(node a,node b){
    return a.num>b.num;
}

void add(int i,int v){
    while(i<=n){
        tree[i]+=v;
        i+=i&-i;
    }
}

int sum(int i){
    int ans=0;
    while(i){
        ans+=tree[i];
        i-=i&-i;
    }
    return ans;
}

void addedge(int u,int v){
    Next[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs(int u){
    dfn[u]=++dfncnt;
    size[u]=1;
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        if(dfn[v])
            continue;
        dfs(v);
        size[u]+=size[v];
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i].num;
        arr[i].id=i;
    }
    for(int i=2;i<=n;i++){
        int u;
        cin>>u;
        addedge(u,i);
    }
    dfs(1);
    sort(arr+1,arr+n+1,cmp);//将能力从高到低排序
    //树状数组查询自己的下级中已经有多少能力比自己强的填了上去
    for(int i=1;i<=n;i++){
        arr[i].sub=dfn[arr[i].id];//改为dfn排名
        ans[arr[i].id]=sum(arr[i].sub+size[arr[i].id]-1)-sum(arr[i].sub);
        add(arr[i].sub,1);
    }
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}
