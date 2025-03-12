//P7402
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;

int n,m;
int arr[MAXN];
int diff[MAXN];
int tree[MAXN<<2][2][2];

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

void up(int u,int mid){
    for(int i=0;i<=1;i++)
		for(int j=0;j<=1;j++)
			if(diff[mid]*diff[mid+1]>=0)
                tree[u][i][j]=tree[u<<1][i][1]+tree[u<<1|1][1][j];//可以合并成一个区间
			else
                tree[u][i][j]=max(tree[u<<1][i][0]+tree[u<<1|1][1][j],tree[u<<1][i][1]+tree[u<<1|1][0][j]); //不能合并成一个区间
}

void build(int l,int r,int i){
    if(l==r){
        tree[i][1][1]=abs(diff[l]);
        return ;
    }
    int mid=(l+r)/2;
    build(l,mid,i<<1);
    build(mid+1,r,i<<1|1);
    up(i,mid);
}

void add(int pos,int l,int r,int i){
    if(l==r){
        tree[i][1][1]=abs(diff[l]);
        return ;
    }
    int mid=(l+r)/2;
    if(pos<=mid){
        add(pos,l,mid,i<<1);
    }
    else{
        add(pos,mid+1,r,i<<1|1);
    }
    up(i,mid);
}

signed main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
        diff[i]=arr[i]-arr[i-1];
    }
    if(n==1){
        cout<<0<<endl;
        return 0;
    }
    diff[1]=0;
    build(2,n,1);
    for(int i=1;i<=m;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        if(u>1){
            diff[u]+=w;
            add(u,2,n,1);
        }
        if(v<n){
            diff[v+1]-=w;
            add(v+1,2,n,1);
        }
        cout<<tree[1][1][1]<<endl;
    }
    return 0;
}
