//对数组进行更新操作，并求最大值
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100001;

long arr[MAXN];
long sum[MAXN << 2];
long change[MAXN << 2];
long Max[MAXN<<2];
bool update[MAXN << 2];
int n,m;

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
void lazy(int i, long v) {
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

void build(int l, int r, int i) {
    if (l == r) {
        Max[i] = arr[l];
    } else {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i);
    }
    change[i] = 0;
    update[i] = false;//初始化每一个位置都没有向下传递的信息
}

// 范围修改
// jobl ~ jobr范围上每个数字变为jobv
void Update(int jobl, int jobr, long jobv, int l, int r, int i) {
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
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>arr[i];
    build(1,n,1);
    long jobv;
    for (int i = 1, op, jobl, jobr; i <= m; i++) {
        cin>>op;
        if (op == 1) {
            cin>>jobl;
            cin>>jobr;
            cin>>jobv;
            Update(jobl, jobr, jobv, 1, n, 1);
        } else {
            cin>>jobl;
            cin>>jobr;
            cout<<query(jobl, jobr, 1, n, 1)<<endl;
        }
    }
    return 0;
}

