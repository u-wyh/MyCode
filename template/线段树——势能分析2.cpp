#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 1e5+5;

int a[MAXN];
int b[MAXN];
int n,m;
struct node{
    int minn;
    int sum;
}tree[MAXN<<2];

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

void up(int i){
    tree[i].minn=min(tree[i<<1].minn,tree[i<<1|1].minn);
    tree[i].sum=tree[i<<1].sum+tree[i<<1|1].sum;
}

void build(int l,int r,int i){
    if(l==r){
        tree[i].minn=a[l]*b[l];
        tree[i].sum=a[l]+b[l];
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl <= l && r <= jobr){
        return tree[i].sum;
    }
    int ans=0;
    int mid=(l+r)>>1;
    if(jobl<=mid){
        ans+=query(jobl,jobr,l,mid,i<<1);
    }
    if(jobr>mid){
        ans+=query(jobl,jobr,mid+1,r,i<<1|1);
    }
    return ans;
}

void add(int pos,int x,int y,int l,int r,int i){
    if(l==r){
        a[pos]=x;
        b[pos]=y;
        tree[i].minn=a[pos]*b[pos];
        tree[i].sum=a[pos]+b[pos];
    }
    else{
        int mid=(l+r)/2;
        if(pos<=mid){
            add(pos,x,y,l,mid,i<<1);
        }
        else{
            add(pos,x,y,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

void update(int jobl,int jobr,int s,int t,int l,int r,int i){
    if(tree[i].minn>s){
        return ;
    }
    if(l==r){
        a[l]+=t;
        b[l]+=t;
        tree[i].minn=a[l]*b[l];
        tree[i].sum=a[l]+b[l];
        return ;
    }
    int mid=(l+r)/2;
    if(jobl<=mid){
        update(jobl,jobr,s,t,l,mid,i<<1);
    }
    if(jobr>mid){
        update(jobl,jobr,s,t,mid+1,r,i<<1|1);
    }
    up(i);
}

signed main()
{
    n=read();
    m=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
    }
    for(int i=1;i<=n;i++){
        b[i]=read();
    }
    build(1,n,1);
    for(int i=1;i<=m;i++){
        int op;
        op=read();
        if(op==1){
            int l,r,s,t;
            l=read(),r=read(),s=read(),t=read();
            update(l,r,s,t,1,n,1);
        }
        else if(op==2){
            int x,y,k;
            k=read(),x=read(),y=read();
            add(k,x,y,1,n,1);
        }
        else{
            int l,r;
            l=read(),r=read();
            cout<<query(l,r,1,n,1)<<endl;
        }
    }
    return 0;
}
