#include<bits/stdc++.h>
using namespace std;
const int MAXN = 10005;

int arr[MAXN];
int change[MAXN << 2];
int Max[MAXN<<2];
bool update[MAXN << 2];
int n,m;
struct block{
    int l,len;
}nums[MAXN];

int collect(int k){
    int sz=1;
    for(int i=1;i<=k;i++){
        arr[sz++]=nums[i].l;
        arr[sz++]=nums[i].l+nums[i].len-1;
    }
    sort(arr+1,arr+sz);
    //cout<<sz;
    int n=1;
    for (int i = 2; i < sz; i++) {
        if (arr[n] != arr[i]) {
            arr[++n] = arr[i];
        }
    }
    return n;
}

void build(int l, int r, int i) {
    if (l < r) {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
    }
    Max[i] = 0;
    change[i] = 0;
    update[i] = false;
}

int Rank(int n, int v) {
    int ans = 0;
    int l = 1, r = n, m;
    while (l <= r) {
        m = (l + r) >> 1;
        if (arr[m] >= v) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    return ans;
}

//比较左右两边最大值
void up(int i) {
    Max[i] = max(Max[i << 1] ,Max[i << 1 | 1]);
}

// 当前的区间对应的信息下标是i
// 现在收到一个懒更新任务 : 这个区间范围上每个数字变为v
// 这个懒更新任务有可能是任务范围把当前线段树范围全覆盖导致的
// 也有可能是父范围的懒信息下发下来的
// 总之把线段树当前范围的Max数组和change   update数组调整好
// 就不再继续往下下发了，懒住了
void lazy(int i, int v) {
    Max[i] = v;
    change[i] = v;
    update[i] = true;//这个数组表示是否有信息可以向下传递
}

// 懒信息的下发
void down(int i) {
    if (update[i]) {
        lazy(i << 1, change[i]);
        lazy(i << 1 | 1, change[i]);
        update[i] = false;
    }
}

// 范围修改
// jobl ~ jobr范围上每个数字变为jobv
void Update(int jobl, int jobr, int jobv, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        lazy(i, jobv);
    } else {
        int mid = (l + r) >> 1;
        down(i);
        if (jobl <= mid) {
            Update(jobl, jobr, jobv, l, mid, i << 1);
        }
        if (jobr > mid) {
            Update(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
        up(i);
    }
}

long query(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return Max[i];
    }
    int mid = (l + r) >> 1;
    down(i);
    long ans = 0;
    if (jobl <= mid) {
        ans =max(ans, query(jobl, jobr, l, mid, i << 1));
    }
    if (jobr > mid) {
        ans =max(ans, query(jobl, jobr, mid + 1, r, i << 1 | 1));
    }
    return ans;
}

int main()
{
    cin>>n;
    m=n;
    for(int i=1;i<=n;i++){
        cin>>nums[i].l>>nums[i].len;
    }
    n=collect(n);
    build(1,n,1);
    int maxans=0;
    for(int i=1;i<=m;i++){
        int l=Rank(n,nums[i].l);
        int r=Rank(n,nums[i].l+nums[i].len-1);
        int h=query(l,r,1,n,1)+nums[i].len;
        maxans=max(maxans,h);
        printf("%d ",maxans);
        Update(l,r,h,1,n,1);
    }
    return 0;
}
