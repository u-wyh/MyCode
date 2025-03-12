// 单点修改的可持久化线段树模版题2，C++版
// 给定一个长度为n的数组arr，下标1~n，一共有m条查询
// 每条查询 l r k : 打印arr[l..r]中第k小的数字
// 1 <= n、m <= 2 * 10^5
// 0 <= arr[i] <= 10^9
// 测试链接 : https://www.luogu.com.cn/problem/P3834
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200001;
const int MAXT = MAXN * 22;

int n, m, s;

// 原始数组
int arr[MAXN];

// 收集权值排序并且去重做离散化
int sorted[MAXN];

// 可持久化线段树需要
// root[i] : 插入arr[i]之后形成新版本的线段树，记录头节点编号
// 0号版本的线段树代表一个数字也没有时，每种名次的数字出现的次数
// i号版本的线段树代表arr[1..i]范围内，每种名次的数字出现的次数
int root[MAXN];
int ls[MAXT];
int rs[MAXT];

// 排名范围内收集了多少个数字
int size[MAXT];
int cnt;

// 返回num在所有值中排名多少
int kth(int num) {
    int left = 1, right = s, mid, ans = 0;
    while (left <= right) {
        mid = (left + right) / 2;
        if (sorted[mid] <= num) {
            ans = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return ans;
}

// 排名范围l~r，建立线段树，返回头节点编号
int build(int l, int r) {
    int rt = ++cnt;
    size[rt] = 0;
    if (l < r) {
        int mid = (l + r) / 2;
        ls[rt] = build(l, mid);
        rs[rt] = build(mid + 1, r);
    }
    return rt;
}

// 排名范围l~r，信息在i号节点，增加一个排名为jobi的数字
// 返回新的头节点编号
int insert(int jobi, int l, int r, int i) {
    int rt = ++cnt;
    ls[rt] = ls[i];
    rs[rt] = rs[i];
    size[rt] = size[i] + 1;//新加一个元素  大小加一
    if (l < r) {
        int mid = (l + r) / 2;
        if (jobi <= mid) {
            ls[rt] = insert(jobi, l, mid, ls[rt]);
        } else {
            rs[rt] = insert(jobi, mid + 1, r, rs[rt]);
        }
    }
    return rt;
}

// 排名范围l~r，老版本信息在u号节点，新版本信息在v号节点
// 返回，第jobk小的数字，排名多少
int query(int jobk, int l, int r, int u, int v) {
    if (l == r) {
        return l;
    }
    int lsize = size[ls[v]] - size[ls[u]];
    int mid = (l + r) / 2;
    if (lsize >= jobk) {
        //如果左半边排名足够 那么就在左半边找
        return query(jobk, l, mid, ls[u], ls[v]);
    } else {
        return query(jobk - lsize, mid + 1, r, rs[u], rs[v]);
    }
}

// 权值做离散化并且去重 + 生成各版本的线段树
void prepare() {
    cnt = 0;
    for (int i = 1; i <= n; i++) {
        sorted[i] = arr[i];
    }
    sort(sorted + 1, sorted + n + 1);
    s = 1;
    for (int i = 2; i <= n; i++) {
        if (sorted[s] != sorted[i]) {
            sorted[++s] = sorted[i];
        }
    }
    root[0] = build(1, s);//建立第一棵树
    for (int i = 1, x; i <= n; i++) {
        x = kth(arr[i]);
        root[i] = insert(x, 1, s, root[i - 1]);
        //每次基于上一个树插入一个元素  建立新树
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    prepare();
    for (int i = 1, l, r, k, rank; i <= m; i++) {
        cin >> l >> r >> k;
        rank = query(k, 1, s, root[l - 1], root[r]);
        cout << sorted[rank] << '\n';
    }
    return 0;
}
