//P1937
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int arr[MAXN];
int tree[MAXN<<2];
int lazy[MAXN<<2];
int n,m;
struct node{
    int l,r;
}nums[MAXN];

bool cmp(node a,node b){
    return a.r==b.r?a.l>b.l:a.r<b.r;
}

void up(int i){
    tree[i]=min(tree[i<<1],tree[i<<1|1]);
}

void build(int l,int r,int i){
    if(l==r){
        tree[i]=arr[l];
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
        int ans=INT_MAX;
        int mid = (l + r) >> 1;
        down(i);
        if (jobl <= mid) {
            ans=min(ans,query(jobl, jobr,l, mid, i << 1));
        }
        if (jobr > mid) {
            ans=min(ans,query(jobl, jobr,mid + 1, r, i << 1 | 1));
        }
        return ans;
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    build(1,n,1);
    for(int i=1;i<=m;i++){
        cin>>nums[i].l>>nums[i].r;
    }
    sort(nums+1,nums+m+1,cmp);
    int ans=0;
    for(int i=1;i<=m;i++){
        if(query(nums[i].l,nums[i].r,1,n,1)>=1){
            add(nums[i].l,nums[i].r,-1,1,n,1);
            ans++;
        }
    }
    cout<<ans<<endl;
    return 0;
}
