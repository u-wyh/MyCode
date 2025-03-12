//P4513
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

struct node{
    int maxv, maxl, maxr, sumv;
}tree[MAXN<<2];
int n, m;
int arr[MAXN];

inline void pushup(node &rt, const node &ls, const node &rs) {
    if (ls.maxr > 0 && rs.maxl > 0)
        rt.maxv = ls.maxr + rs.maxl;
    else {
        //这个地方一定要写  因为一开始初始时为0  这是什么都没有选
        rt.maxv = max(ls.maxr , rs.maxl);
    }
    rt.maxv = max(rt.maxv, ls.maxv);
    rt.maxv = max(rt.maxv, rs.maxv);
    rt.maxl = max(ls.maxl, ls.sumv + rs.maxl);
    rt.maxr = max(rs.maxr, rs.sumv + ls.maxr);
    rt.sumv = ls.sumv + rs.sumv;
}

void build(int l, int r, int i) {
    if (l == r) {
        tree[i].maxv = tree[i].maxl = tree[i].maxr = tree[i].sumv = arr[l];
    } else {
        int mid = (l + r) / 2;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        pushup(tree[i], tree[i << 1], tree[i << 1 | 1]);
    }
}

void update(int pos, int val, int l, int r, int i) {
    if (l == r) {
        tree[i].maxv = tree[i].maxl = tree[i].maxr = tree[i].sumv = val;
    } else {
        int mid = (l + r) / 2;
        if (pos <= mid) {
            update(pos, val, l, mid, i << 1);
        } else {
            update(pos, val, mid + 1, r, i << 1 | 1);
        }
        pushup(tree[i], tree[i << 1], tree[i << 1 | 1]);
    }
}

node query(int ql, int qr, int l, int r, int i) {
    if (ql <= l && r <= qr) {
        return tree[i];
    } else {
        int mid = (l + r) / 2;
        if (ql <= mid && mid < qr) {
            node ls = query(ql, qr, l, mid, i << 1);
            node rs = query(ql, qr, mid + 1, r, i << 1 | 1);
            node res;
            pushup(res, ls, rs);
            return res;
        } else if (ql <= mid) {
            return query(ql, qr, l, mid, i << 1);
        } else {
            return query(ql, qr, mid + 1, r, i << 1 | 1);
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    build(1, n, 1);
    for (int i = 1; i <= m; i++) {
        int op, a, b;
        cin >> op >> a >> b;
        if (op == 1) {
            if (a > b) swap(a, b);
            cout << query(a, b, 1, n, 1).maxv << endl;
        } else {
            update(a, b, 1, n, 1);
        }
    }
    return 0;
}
