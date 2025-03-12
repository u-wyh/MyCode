#include<bits/stdc++.h>
using namespace std;
const int MAXN = 50005;

int n,m;
int len[MAXN<<2];
int pre[MAXN<<2];
int suf[MAXN<<2];
int change[MAXN<<2];
bool update[MAXN<<2];

void up(int i,int ln,int rn){
    int l=i<<1;
    int r=i<<1|1;
    len[i]=max(max(len[l],len[r]),suf[l]+pre[r]);
    pre[i]=len[l]<ln?pre[l]:pre[l]+pre[r];
    suf[i]=suf[r]<rn?suf[r]:suf[l]+suf[r];
}

void lazy(int i,int v,int n){
    len[i]=pre[i]=suf[i]= v==0 ?n:0;
    change[i]=v;
    update[i]=true;
}

void down(int i,int ln,int rn){
    if(update[i]){
        lazy(i<<1,change[i],ln);
        lazy(i<<1|1,change[i],rn);
        update[i]=false;
    }
}

void build(int l,int r,int i){
    if(l==r){
        len[i]=1;
        suf[i]=1;
        pre[i]=1;
    }else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i,mid-l+1,r-mid);
    }
}


void Update(int jobl, int jobr, int jobv, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        lazy(i, jobv, r - l + 1);
    } else {
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        if (jobl <= mid) {
            Update(jobl, jobr, jobv, l, mid, i << 1);
        }
        if (jobr > mid) {
            Update(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
        up(i, mid - l + 1, r - mid);
    }
}

int queryLeft(int x, int l, int r, int i) {
    if (l == r) {
        return l;
    } else {
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        // 最先查左边
        if (len[i << 1] >= x) {
            return queryLeft(x, l, mid, i << 1);
        }
        // 然后查中间向两边扩展的可能区域
        if (suf[i << 1] + pre[i << 1 | 1] >= x) {
            return mid - suf[i << 1] + 1;
        }
        // 前面都没有再最后查右边
        return queryLeft(x, mid + 1, r, i << 1 | 1);
    }
}

int main()
{
    cin>>n>>m;
    build(1,n,1);
    for (int i = 1, op, x, y, left; i <= m; i++) {
        cin>>op;
        if (op == 1) {
            cin>>x;
            if (len[1] < x) {
                left = 0;
            } else {
                left = queryLeft(x, 1, n, 1);
                Update(left, left + x - 1, 1, 1, n, 1);
            }
            cout<<left<<endl;
        } else {
            cin>>x>>y;
            Update(x, min(x + y - 1, n), 0, 1, n, 1);
        }
    }
    return 0;
}
