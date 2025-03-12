//P3792.cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e5+5;

int n,m;
int arr[MAXN];
struct node{
    int minn,maxx,sum,squ;
}tree[MAXN<<2];

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

node up(node l,node r){
    node u;
    u.minn=min(l.minn,r.minn);
    u.maxx=max(l.maxx,r.maxx);
    u.sum=l.sum+r.sum;
    u.squ=(l.squ+r.squ);
    return u;
}

void build(int l,int r,int i){
    if(l==r){
        tree[i].minn=tree[i].maxx=tree[i].sum=arr[l];
        tree[i].squ=(arr[l]*arr[l]);
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        tree[i]=up(tree[i<<1],tree[i<<1|1]);
    }
}

void update(int pos,int jobv,int l,int r,int i){
    if(l==r){
        tree[i].minn=tree[i].maxx=tree[i].sum=jobv;
        tree[i].squ=(jobv*jobv);
    }
    else{
        int mid=(l+r)/2;
        if(pos<=mid){
            update(pos,jobv,l,mid,i<<1);
        }
        else{
            update(pos,jobv,mid+1,r,i<<1|1);
        }
        tree[i]=up(tree[i<<1],tree[i<<1|1]);
    }
}

node query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int mid=(l+r)/2;
        if(jobl<=mid&&jobr>mid){
            return up(query(jobl,jobr,l,mid,i<<1),query(jobl,jobr,mid+1,r,i<<1|1));
        }
        else if(jobl<=mid){
            return query(jobl,jobr,l,mid,i<<1);
        }
        else{
            return query(jobl,jobr,mid+1,r,i<<1|1);
        }
    }
}

signed main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
    }
    build(1,n,1);
    for(int i=1;i<=m;i++){
        int op,u,v;
        op=read(),u=read(),v=read();
        if(op==1){
            update(u,v,1,n,1);
        }
        else{
            node now=query(u,v,1,n,1);
            int l=now.minn,r=now.maxx;
            if((now.sum!=(l+r)*(r-l+1)/2)||(now.squ!=(r*(r+1)*(2*r+1)-(l-1)*l*(2*l-1))/6)){
                cout<<"yuanxing"<<endl;
            }
            else{
                cout<<"damushen"<<endl;
            }
        }
    }
    return 0;
}
