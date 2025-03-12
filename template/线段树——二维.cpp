//P2862
//这道题要特别注意  涉及到了负数 那么取中指的时候不能用除以2  要用>>1
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 505;
const int MAXM = 1e4+10;

int c,n;
struct point{
    int x,y;
}nums[MAXN];
int ans,tot;
int tree[MAXM<<4],lazy[MAXM<<4];//因为这里是正负两个区间
struct node{
    int x,l,r,val;
}p[MAXN<<1];

inline int cmp(node x,node y){
	if(x.x==y.x)
        return x.val<y.val;
	return x.x<y.x;
}

void pushup(int i,int val){
    tree[i]+=val;
    lazy[i]+=val;
}

void pushdown(int i){
    if(lazy[i]){
        pushup(i<<1,lazy[i]);
        pushup(i<<1|1,lazy[i]);
        lazy[i]=0;
    }
}

void update(int jobl,int jobr,int jobv,int l,int r,int i){
    //cout<<777<<endl;
    if(jobl<=l&&r<=jobr){
        pushup(i,jobv);
    }
    else{
        pushdown(i);
        int mid=(l+r)>>1;
        if(jobl<=mid)
            update(jobl,jobr,jobv,l,mid,i<<1);
        if(jobr>mid)
            update(jobl,jobr,jobv,mid+1,r,i<<1|1);
        tree[i]=max(tree[i<<1],tree[i<<1|1]);
    }
}

void build(int l,int r,int i){
    //cout<<l<<' '<<r<<' '<<i<<endl;
    tree[i]=0,lazy[i]=0;
    if(l==r){
        return ;
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
    }
}

bool check(int len){
    build(-MAXM,MAXM,1);
    //cout<<999<<endl;
    tot=0;
	for(int i=1;i<=n;i++){
		p[++tot]=(node){nums[i].x,nums[i].y-len+1,nums[i].y,1};
		p[++tot]=(node){nums[i].x+len,nums[i].y-len+1,nums[i].y,-1};
	}
	sort(p+1,p+1+tot,cmp);
	for(int i=1;i<=tot;i++){
        //cout<<888<<endl;
		update(p[i].l,p[i].r,p[i].val,-MAXM,MAXM,1);
		if(tree[1]>=c)
            return true;
	}
	return 0;
}

int main()
{
    cin>>c>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i].x>>nums[i].y;
    }
    int l=1,r=10005;
    while(l<=r){
        //cout<<666<<endl;
        int mid=(l+r)/2;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }else{
            l=mid+1;
        }
    }
    cout<<ans<<endl;
    return 0;
}
