//P7119
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;

struct node{
    int l=0,r=0,cnt=0,sum=0,lazy=0;
    //分别表示  左右边界  区间上反面向上的数目以及相应位置之和  懒信息(只能是0或1)
}tree[MAXN<<2];
int n,m;
char s[MAXN];

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

void up(int i){
    tree[i].cnt=tree[i<<1].cnt+tree[i<<1|1].cnt;
    tree[i].sum=tree[i<<1].sum+tree[i<<1|1].sum;
}

void build(int l,int r,int i){
    tree[i].l=l,tree[i].r=r,tree[i].lazy=0;
    if(l==r){
        if(s[l]=='T'){
            tree[i].cnt=1;
            tree[i].sum=l;
        }
        else{
            tree[i].cnt=0;
            tree[i].sum=0;
        }
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
    //cout<<i<<": "<<tree[i].l<<' '<<tree[i].r<<' '<<tree[i].lazy<<' '<<tree[i].cnt<<' '<<tree[i].sum<<endl;
}

void downlazy(int i){
    tree[i].lazy^=1;
    tree[i].cnt=tree[i].r-tree[i].l+1-tree[i].cnt;
    tree[i].sum=(tree[i].r-tree[i].l+1)*(tree[i].r+tree[i].l)/2-tree[i].sum;
}

void down(int i){
    if(tree[i].lazy){
        downlazy(i<<1);
        downlazy(i<<1|1);
        tree[i].lazy=0;
    }
}

void update(int jobl,int jobr,int l,int r,int i){
    //cout<<l<<' '<<r<<' '<<i<<endl;
    if(jobl<=l&&r<=jobr){
        downlazy(i);
    }
    else{
        down(i);
        int mid=(l+r)>>1;
        if(jobl<=mid)
            update(jobl,jobr,l,mid,i<<1);
        if(jobr>mid)
            update(jobl,jobr,mid+1,r,i<<1|1);
        up(i);
    }
}

signed main()
{
    n=read(),m=read();
    scanf("%s",s+1);
    build(1,n,1);
    cout<<2*tree[1].sum-tree[1].cnt*tree[1].cnt<<endl;
    for(int i=1;i<=m;i++){
        int l,r;
        l=read(),r=read();
        update(l,r,1,n,1);
		cout<<2*tree[1].sum-tree[1].cnt*tree[1].cnt<<endl;
    }
    return 0;
}
