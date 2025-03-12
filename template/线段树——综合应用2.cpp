#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;

int arr[MAXN];
long sum[MAXN << 2];
long Max[MAXN<<2];
int n,m;

// 累加和信息的汇总
void up(int i) {
    // 父范围的累加和 = 左范围累加和 + 右范围累加和
    Max[i] = max(Max[i << 1] ,Max[i << 1 | 1]);
    sum[i] = sum[i << 1]+sum[i << 1 | 1];
}

// 建树
void build(int l, int r, int i) {
    if (l == r) {
        Max[i] = arr[l];
        sum[i] = arr[l];
    } else {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i);
    }
}

void mod(int jobl, int jobr, int jobv, int l, int r, int i) {
    if (jobv > Max[i]) {
        return ;
    }
    if (l == r) {
        sum[i] %= jobv;
        Max[i] %= jobv;
    } else {
        int mid = (l + r) >> 1;
        if (jobl <= mid) {
            mod(jobl, jobr, jobv, l, mid, i << 1);
        }
        if (jobr > mid) {
            mod(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
        up(i);
    }
}

void Update(int jobl, long jobv, int l, int r, int i) {
    if (l==r) {
        sum[i]=jobv;
        Max[i]=jobv;
    } else {
        int mid = (l + r) >> 1;
        if (jobl <= mid) {
            Update(jobl, jobv, l, mid, i << 1);
        }else {
            Update(jobl, jobv, mid + 1, r, i << 1 | 1);
        }
        up(i);
    }
}

long query(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return sum[i];
    }
    int mid = (l + r) >> 1;
    long ans = 0;
    if (jobl <= mid) {
        ans +=query(jobl, jobr, l, mid, i << 1);
    }
    if (jobr > mid) {
        ans +=query(jobl, jobr, mid + 1, r, i << 1 | 1);
    }
    return ans;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>arr[i];
    build(1,n,1);
    long jobv;
    for (int i = 1, op, jobl, jobr; i <= m; i++) {
        cin>>op;
        if (op == 3) {
            cin>>jobl;
            cin>>jobv;
            Update(jobl, jobv, 1, n, 1);
        } else if(op == 2){
            cin>>jobl>>jobr>>jobv;
            mod(jobl, jobr, jobv, 1, n, 1);
        } else {
            cin>>jobl>>jobr;
            cout<<query(jobl, jobr, 1, n, 1)<<endl;
        }
    }
    return 0;
}
