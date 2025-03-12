//P3373
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN =1e5+5;

int n,m,mod;
struct node{
    int val,mul,add;
}tree[MAXN<<2];
int arr[MAXN];

void up(int i){
    tree[i].val=tree[i<<1].val+tree[i<<1|1].val;
    tree[i].val%=mod;
}

void build(int l,int r,int i){
    tree[i].mul=1,tree[i].add=0;
    if(l==r){
        tree[i].val=arr[l];
        tree[i].val%=mod;
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
    //cout<<tree[i].val<<' ';
}

void mullazy(int i,int val){
    tree[i].val*=val;
    tree[i].add*=val;
    tree[i].mul*=val;
    tree[i].val%=mod;
    tree[i].add%=mod;
    tree[i].mul%=mod;
}

void addlazy(int i,int val,int l,int r){
    tree[i].add+=val;
    tree[i].val+=val*(r-l+1);
    tree[i].val%=mod;
    tree[i].add%=mod;
}

void down(int i,int l,int r){
    if(tree[i].mul!=1){
        mullazy(i<<1,tree[i].mul);
        mullazy(i<<1|1,tree[i].mul);
        tree[i].mul=1;
    }
    if(tree[i].add){
        addlazy(i<<1,tree[i].add,l,(l+r)/2);
        addlazy(i<<1|1,tree[i].add,(l+r)/2+1,r);
        tree[i].add=0;
    }
}

void mul(int jobl,int jobr,int val,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        mullazy(i,val);
    }
    else{
        int mid=(l+r)/2;
        down(i,l,r);
        if(jobl<=mid){
            mul(jobl,jobr,val,l,mid,i<<1);
        }
        if(jobr>mid){
            mul(jobl,jobr,val,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

void add(int jobl,int jobr,int val,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        addlazy(i,val,l,r);
    }
    else{
        int mid=(l+r)/2;
        down(i,l,r);
        if(jobl<=mid){
            add(jobl,jobr,val,l,mid,i<<1);
        }
        if(jobr>mid){
            add(jobl,jobr,val,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    //cout<<' '<<l<<' '<<r<<endl;
    if(jobl<=l&&r<=jobr){
        return tree[i].val;
    }
    else{
        int mid=(l+r)/2;
        down(i,l,r);
        int ans=0;
        if(jobl<=mid){
            ans=(ans+query(jobl,jobr,l,mid,i<<1))%mod;
        }
        if(jobr>mid){
            ans=(ans+query(jobl,jobr,mid+1,r,i<<1|1))%mod;
        }
        return ans;
    }
}

signed main()
{
    cin>>n>>m>>mod;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    build(1,n,1);
    for(int i=1;i<=m;i++){
        int op,x,y,v;
        cin>>op>>x>>y;
        if(op==1){
            cin>>v;
            mul(x,y,v,1,n,1);
        }
        else if(op==2){
            cin>>v;
            add(x,y,v,1,n,1);
        }
        else{
            v=query(x,y,1,n,1);
            v%=mod;
            cout<<v<<endl;
        }
    }
    return 0;
}
