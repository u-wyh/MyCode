#include<bits/stdc++.h>
using namespace std;
const int MAXN = 20001;

struct node{
    int val,sub;
}nums[MAXN];
// 维护线段树一段范围，候选是谁
int cand[MAXN << 2];
// 维护线段树一段范围，候选血量
int hp[MAXN << 2];
int n;
int arr[MAXN];

bool cmp(node a,node b){
    if(a.val==b.val)
        return a.sub<b.sub;
    else
        return a.val<b.val;
}

void buildCnt() {
    for (int i = 0; i < n; i++) {
        nums[i].val = arr[i];
        nums[i].sub = i;
    }
    sort(nums,nums + n, cmp);
}

// arr[0 ~ i]范围上
// (<v的数) + (==v但下标<=i的数)，有几个
int bs(int v, int i) {
    int left = 0, right = n - 1, mid;
    int find = -1;
    while (left <= right) {
        mid = (left + right) >> 1;
        if (nums[mid].val < v || (nums[mid].val == v && nums[mid].sub <= i)) {
            find = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return find + 1;
}

int cnt(int l, int r, int v) {
    return bs(v, r) - bs(v, l - 1);
}

void up(int i) {
    int lc = cand[i << 1], lh = hp[i << 1];
    int rc = cand[i << 1 | 1], rh = hp[i << 1 | 1];
    cand[i] = lc == rc || lh >= rh ? lc : rc;
    hp[i] = lc == rc ? (lh + rh) : abs(lh - rh);
}

void buildTree(int l, int r, int i) {
    if (l == r) {
        cand[i] = arr[l - 1];
        hp[i] = 1;
    } else {
        int mid = (l + r) >> 1;
        buildTree( l, mid, i << 1);
        buildTree( mid + 1, r, i << 1 | 1);
        up(i);
    }
}

int[] findCandidate(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return new int[] { cand[i], hp[i] };
    } else {
        int mid = (l + r) >> 1;
        if (jobr <= mid) {
            return findCandidate(jobl, jobr, l, mid, i << 1);
        }
        if (jobl > mid) {
            return findCandidate(jobl, jobr, mid + 1, r, i << 1 | 1);
        }
        int[] lch = findCandidate(jobl, jobr, l, mid, i << 1);
        int[] rch = findCandidate(jobl, jobr, mid + 1, r, i << 1 | 1);
            int lc = lch[0], lh = lch[1];
        int rc = rch[0], rh = rch[1];
            int c = lc == rc || lh >= rh ? lc : rc;
        int h = lc == rc ? (lh + rh) : Math.abs(lh - rh);
            return new int[] { c, h };
    }
}

int main()
{
    cin>>n;

    return 0;
}
