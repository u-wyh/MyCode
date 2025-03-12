#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;

int n,m;
int diff[MAXN];
long sum[MAXN<<2];
int add[MAXN<<2];

void up(int i) {
    // 父范围的累加和 = 左范围累加和 + 右范围累加和
    sum[i] = sum[i << 1] + sum[i << 1 | 1];
}

void lazy(int i, long v, int n) {
    sum[i] += v * n;
    add[i] += v;
}

// 懒信息的下发
void down(int i, int ln, int rn) {
    if (add[i] != 0) {
        // 发左
        lazy(i << 1, add[i], ln);
        // 发右
        lazy(i << 1 | 1, add[i], rn);
        // 父范围懒信息清空
        add[i] = 0;
    }
}

void build(int l, int r, int i) {
    if (l == r) {
        sum[i] = diff[l];
    } else {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i);
    }
    add[i] = 0;
}

void Add(int jobl, int jobr, long jobv, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        lazy(i, jobv, r - l + 1);
    } else {
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        if (jobl <= mid) {
            Add(jobl, jobr, jobv, l, mid, i << 1);
        }
        if (jobr > mid) {
            Add(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
        up(i);//汇总修改数据
    }
}

long query(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return sum[i];
    }
    int mid = (l + r) >> 1;
    down(i, mid - l + 1, r - mid);
    long ans = 0;
    if (jobl <= mid) {
        ans += query(jobl, jobr, l, mid, i << 1);
    }
    if (jobr > mid) {
        ans += query(jobl, jobr, mid + 1, r, i << 1 | 1);
    }
    return ans;
}

int main()
{
    cin>>n>>m;
    int cur,pre=0;
    for(int i=1;i<=n;i++){
        cin>>cur;
        diff[i]=cur-pre;
        pre=cur;
        //printf("%3d",diff[i]);
    }
    //printf("\n");
    build(1,n,1);
    int l,r,op,p;
    long k,d;
    for(int i=1;i<=m;i++){
        cin>>op;
        if(op==1){
            cin>>l>>r>>k>>d;
            long e=k+d*(r-l);
            Add(l,l,k,1,n,1);
            if(l+1<=r)
                Add(l+1,r,d,1,n,1);
            if(r<n)
                Add(r+1,r+1,-e,1,n,1);
        }else{
            cin>>p;
            cout<<query(1,p,1,n,1)<<endl;
        }
    }
    return 0;
}
