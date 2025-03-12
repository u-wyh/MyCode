#include<bits/stdc++.h>
using namespace std;
const int MAXN = 10005;

int arr[MAXN];
int sum[MAXN << 2];
int change[MAXN << 2];
bool update[MAXN << 2];
int n,m;
int ans[2];

// 累加和信息的汇总
void up(int i) {
    // 父范围的累加和 = 左范围累加和 + 右范围累加和
    sum[i] = sum[i << 1] + sum[i << 1 | 1];
}

// 当前的区间对应的信息下标是i
// 现在收到一个懒更新任务 : 这个区间范围上每个数字变为v
// 这个懒更新任务有可能是任务范围把当前线段树范围全覆盖导致的
// 也有可能是父范围的懒信息下发下来的
// 总之把线段树当前范围的sum数组和change   update数组调整好
// 就不再继续往下下发了，懒住了
void lazy(int i, long v, int n) {
    sum[i] = v * n;
    change[i] = v;
    update[i] = true;
}

// 懒信息的下发
void down(int i, int ln, int rn) {
    if (update[i]) {
        lazy(i << 1, change[i], ln);
        lazy(i << 1 | 1, change[i], rn);
        update[i] = false;
    }
}

void build(int l, int r, int i) {
    if (l < r) {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
    }
    sum[i] = 0;
    update[i] = false;
}

// 范围修改
// jobl ~ jobr范围上每个数字变为jobv
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
        up(i);
    }
}

int query(int jobl, int jobr, int l, int r, int i) {
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

int findZero(int s, int k) {
    int l = s, r = n, mid;
    int ans = 0;
    while (l <= r) {
        mid = (l + r) >> 1;
        if (mid - s + 1 - query(s, mid, 1, n, 1) >= k) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}

int Clear(int left, int right) {
    left++;
    right++;
    int ans = query(left, right, 1, n, 1);
    Update(left, right, 0, 1, n, 1);
    return ans;
}

void Insert(int from, int flowers) {
    // 题目给的位置从0开始
    // 线段树下标从1开始
    from++;
    int zeros = n - from + 1 - query(from, n, 1, n, 1);
    if (zeros == 0) {
        ans[0] = 0;
        ans[1] = 0;
    } else {
        ans[0] = findZero(from, 1);
        ans[1] = findZero(from, min(zeros, flowers));
        Update(ans[0], ans[1], 1, 1, n, 1);
    }
    // 题目需要从0开始的下标
    ans[0]--;
    ans[1]--;
}

int main()
{
    cin>>n>>m;
    build(1,n,1);
    long jobv;
    for (int i = 1, op; i <= m; i++) {
        cin>>op;
        if (op == 1) {
            int from;
            int flowers;
            cin>>from;
            cin>>flowers;
            Insert(from,flowers);
            if(ans[0]==-1){
                printf("can not put any one\n");
            }else{
                cout<<ans[0]<<' '<<ans[1]<<endl;
            }
        } else {
            int left,right;
            cin>>left>>right;
            cout<<Clear(left,right)<<endl;
        }
    }
    return 0;
}
