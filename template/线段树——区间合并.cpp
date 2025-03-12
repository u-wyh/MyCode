#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100001;

// 原始数组
int arr[MAXN];
// 累加和用来统计1的数量
int sum[MAXN << 2];
// 连续0的最长子串长度
int len0[MAXN << 2];
// 连续0的最长前缀长度
int pre0[MAXN << 2];
// 连续0的最长后缀长度
int suf0[MAXN << 2];
// 连续1的最长子串长度
int len1[MAXN << 2];
// 连续1的最长前缀长度
int pre1[MAXN << 2];
// 连续1的最长后缀长度
int suf1[MAXN << 2];
// 懒更新信息，范围上所有数字被重置成了什么
int change[MAXN << 2];
// 懒更新信息，范围上有没有重置任务
bool update[MAXN << 2];
// 懒更新信息，范围上有没有翻转任务
bool reversE[MAXN << 2];

int ans[3];

void up(int i, int ln, int rn) {
    int l = i << 1;
    int r = i << 1 | 1;
    sum[i] = sum[l] + sum[r];
    len0[i] = max(max(len0[l], len0[r]), suf0[l] + pre0[r]);
    pre0[i] = len0[l] < ln ? pre0[l] : (pre0[l] + pre0[r]);
    suf0[i] = len0[r] < rn ? suf0[r] : (suf0[l] + suf0[r]);
    len1[i] = max(max(len1[l], len1[r]), suf1[l] + pre1[r]);
    pre1[i] = len1[l] < ln ? pre1[l] : (pre1[l] + pre1[r]);
    suf1[i] = len1[r] < rn ? suf1[r] : (suf1[l] + suf1[r]);
}

void updateLazy(int i, int v, int n) {
    sum[i] = v * n;
    len0[i] = pre0[i] = suf0[i] = v == 0 ? n : 0;
    len1[i] = pre1[i] = suf1[i] = v == 1 ? n : 0;
    change[i] = v;
    update[i] = true;
    reversE[i] = false;
}

void reverseLazy(int i, int n) {
    sum[i] = n - sum[i];
    int tmp;
    tmp = len0[i]; len0[i] = len1[i]; len1[i] = tmp;
    tmp = pre0[i]; pre0[i] = pre1[i]; pre1[i] = tmp;
    tmp = suf0[i]; suf0[i] = suf1[i]; suf1[i] = tmp;
    reversE[i] = !reversE[i];
}

void down(int i, int ln, int rn) {
    if (update[i]) {
        updateLazy(i << 1, change[i], ln);
        updateLazy(i << 1 | 1, change[i], rn);
        update[i] = false;
    }
    if (reversE[i]) {
        reverseLazy(i << 1, ln);
        reverseLazy(i << 1 | 1, rn);
        reversE[i] = false;
    }
}

void build(int l, int r, int i) {
    if (l == r) {
        sum[i] = arr[l];
        len0[i] = pre0[i] = suf0[i] = arr[l] == 0 ? 1 : 0;
        len1[i] = pre1[i] = suf1[i] = arr[l] == 1 ? 1 : 0;
    } else {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i, mid - l + 1, r - mid);
    }
    update[i] = false;
    reversE[i] = false;
}

void Update(int jobl, int jobr, int jobv, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        updateLazy(i, jobv, r - l + 1);
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

void Reverse(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        reverseLazy(i, r - l + 1);
    } else {
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        if (jobl <= mid) {
            Reverse(jobl, jobr, l, mid, i << 1);
        }
        if (jobr > mid) {
            Reverse(jobl, jobr, mid + 1, r, i << 1 | 1);
        }
        up(i, mid - l + 1, r - mid);
    }
}

// 线段树范围l~r上，被jobl~jobr影响的区域里，返回1的数量
int querySum(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return sum[i];
    }
    int mid = (l + r) >> 1;
    down(i, mid - l + 1, r - mid);
    int ans = 0;
    if (jobl <= mid) {
        ans += querySum(jobl, jobr, l, mid, i << 1);
    }
    if (jobr > mid) {
        ans += querySum(jobl, jobr, mid + 1, r, i << 1 | 1);
    }
    return ans;
}

// 返回一个长度为3的数组ans，代表结果，具体含义如下：
// ans[0] : 线段树范围l~r上，被jobl~jobr影响的区域里，连续1的最长子串长度
// ans[1] : 线段树范围l~r上，被jobl~jobr影响的区域里，连续1的最长前缀长度
// ans[2] : 线段树范围l~r上，被jobl~jobr影响的区域里，连续1的最长后缀长度
void queryLongest(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        ans[0]=len1[i],ans[1]=pre1[i],ans[2]=suf1[i];
        return ;
    } else {
        int mid = (l + r) >> 1;
        int ln = mid - l + 1;
        int rn = r - mid;
        down(i, ln, rn);
        if (jobr <= mid) {
            queryLongest(jobl, jobr, l, mid, i << 1);
            return ;
        }
        if (jobl > mid) {
            queryLongest(jobl, jobr, mid + 1, r, i << 1 | 1);
            return ;
        }
        int l3[3];
        queryLongest(jobl, jobr, l, mid, i << 1);
        l3[0]=ans[0],l3[1]=ans[1],l3[2]=ans[2];
        int r3[3];
        queryLongest(jobl, jobr, mid + 1, r, i << 1 | 1);
        r3[0]=ans[0],r3[1]=ans[1],r3[2]=ans[2];
        int llen = l3[0], lpre = l3[1], lsuf = l3[2];
        int rlen = r3[0], rpre = r3[1], rsuf = r3[2];
        ans[0] = max(max(llen, rlen), lsuf + rpre);
        // 任务实际影响了左侧范围的几个点 -> mid - Math.max(jobl, l) + 1
        ans[1]= llen < (mid - max(jobl, l) + 1 )? lpre : (lpre + rpre);
        // 任务实际影响了右侧范围的几个点 -> Math.min(r, jobr) - mid
        ans[2] = rlen < (min(r, jobr) - mid )? rsuf : (lsuf + rsuf);
        return ;
    }
}

int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    build(1,n,1);
    int op,L,R;
    for(int i=1;i<=m;i++){
        cin>>op>>L>>R;
        L++,R++;
        if(op==0){
            Update(L,R,0,1,n,1);
        }else if(op==1){
            Update(L,R,1,1,n,1);
        }else if(op==2){
            Reverse(L,R,1,n,1);
        }else if(op==3){
            cout<<querySum(L,R,1,n,1)<<endl;
        }else{
            queryLongest(L,R,1,n,1);
            cout<<ans[0]<<endl;
        }
    }
    return 0;
}


