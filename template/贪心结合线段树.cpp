//P1607
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 20005;
const int MAXK = 50005;

int k,n,c;
struct node{
    int l,r,num;
}arr[MAXK];
int tree[MAXN<<2];
int lazy[MAXN<<2];

void up(int i){
    tree[i]=max(tree[i<<1],tree[i<<1|1]);
}

void build(int l,int r,int i){
    if(l==r){
        return;
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void downlazy(int i,int v){
    tree[i]+=v;
    lazy[i]+=v;
}

void down(int i){
    if(lazy[i]){
        downlazy(i<<1,lazy[i]);
        downlazy(i<<1|1,lazy[i]);
        lazy[i]=0;
    }
}

void add(int jobl, int jobr, int jobv, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        downlazy(i, jobv);
    } else {
        int mid = (l + r) >> 1;
        down(i);
        if (jobl <= mid) {
            add(jobl, jobr, jobv, l, mid, i << 1);
        }
        if (jobr > mid) {
            add(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
        up(i);//汇总修改数据
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if (jobl <= l && r <= jobr) {
        return tree[i];
    } else {
        int ans=0;
        int mid = (l + r) >> 1;
        down(i);
        if (jobl <= mid) {
            ans=max(ans,query(jobl, jobr,l, mid, i << 1));
        }
        if (jobr > mid) {
            ans=max(ans,query(jobl, jobr,mid + 1, r, i << 1 | 1));
        }
        return ans;
    }
}

bool cmp(node a,node b){
    return a.r<b.r;
}

int main()
{
    cin>>k>>n>>c;
    for(int i=1;i<=k;i++){
        cin>>arr[i].l>>arr[i].r>>arr[i].num;
    }
    sort(arr+1,arr+k+1,cmp);
    int ans=0;
    for(int i=1;i<=k;i++){
        int l=arr[i].l;
        int r=arr[i].r;
        int mx=query(l,r-1,1,n,1);
        int x=min(c-mx,arr[i].num);
        add(l,r-1,x,1,n,1);
        ans+=x;
    }
    cout<<ans<<endl;
    return 0;
}
