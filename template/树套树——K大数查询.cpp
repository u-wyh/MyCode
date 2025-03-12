// k大数查询，C++版
// 初始时有n个空集合，编号1~n，实现如下两种类型的操作，操作一共发生m次
// 操作 1 l r v : 数字v放入编号范围[l,r]的每一个集合中
// 操作 2 l r k : 编号范围[l,r]的所有集合，如果生成不去重的并集，返回第k大的数字
// 1 <= n、m <= 5 * 10^4
// -n <= v <= +n
// 1 <= k < 2^63，题目保证第k大的数字一定存在
// 测试链接 : https://www.luogu.com.cn/problem/P3332
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
//这道题的外层是数字大写比如1 2 3 内层对应的是arr
//这道题目是根据数字的排名确定外层树
//即如果再jobl到jobr集合中加入一个排名为jobv的数字
//那么外层范围中包含jobv的树都要将jobl到jobr的集合中元素个数加一
//内层树是根据集合的编号划分
#include <bits/stdc++.h>
using namespace std;
// 外部线段树的范围，一共只有m个操作，所以最多有m种数字
const int MAXM = 50001;
// 内部线段树的节点数上限
const int MAXT = MAXM * 230;

int n, m, s;
// 所有操作收集起来，因为牵扯到数字离散化
int ques[MAXM][4];
// 所有可能的数字，收集起来去重，方便得到数字排名
int sorted[MAXM];

// 外部(a~b) + 内部(c~d)表示：数字排名范围a~b，集合范围c~d，数字的个数
// 外部线段树的下标表示数字的排名
// 外部(a~b)，假设对应的节点编号为i，那么root[i]就是内部线段树的头节点编号
int root[MAXM << 2];

// 内部线段树是开点线段树，所以需要cnt来获得节点计数
// 内部线段树的下标表示集合的编号
// 内部(c~d)，假设对应的节点编号为i
// sum[i]表示集合范围c~d，一共收集了多少数字
// lazy[i]懒更新信息，集合范围c~d，增加了几个数字，等待懒更新的下发
int ls[MAXT];
int rs[MAXT];
long long sum[MAXT];
int lazy[MAXT];
int cnt;

int kth(int num) {
    int l = 1, r = s;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (sorted[mid] == num) {
            return mid;
        } else if (sorted[mid] < num) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return -1;
}

void up(int i) {
    sum[i] = sum[ls[i]] + sum[rs[i]];
}

void down(int i, int ln, int rn) {
    if (lazy[i]) {
        if (!ls[i]) ls[i] = ++cnt;
        if (!rs[i]) rs[i] = ++cnt;
        sum[ls[i]] += 1LL * lazy[i] * ln;
        lazy[ls[i]] += lazy[i];
        sum[rs[i]] += 1LL * lazy[i] * rn;
        lazy[rs[i]] += lazy[i];
        lazy[i] = 0;
    }
}

//在内部集合jobl~jobr中加入一个数字
int innerAdd(int jobl, int jobr, int l, int r, int i) {
    if (!i) i = ++cnt;
    if (jobl <= l && r <= jobr) {
        sum[i] += (long long)(r - l + 1);
        lazy[i]++;
    } else {
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        if (jobl <= mid) ls[i] = innerAdd(jobl, jobr, l, mid, ls[i]);
        if (jobr > mid) rs[i] = innerAdd(jobl, jobr, mid + 1, r, rs[i]);
        up(i);
    }
    return i;
}

//查询内部集合中jobl到jobr区间有多少个元素
long long innerQuery(int jobl, int jobr, int l, int r, int i) {
    if (!i) return 0;
    if (jobl <= l && r <= jobr) {
        return sum[i];
    }
    int mid = (l + r) >> 1;
    down(i, mid - l + 1, r - mid);
    long long ans = 0;
    if (jobl <= mid) ans += innerQuery(jobl, jobr, l, mid, ls[i]);
    if (jobr > mid) ans += innerQuery(jobl, jobr, mid + 1, r, rs[i]);
    return ans;
}

//在外部中加入一个大小为jobv的数字到jobl~jobr的集合  这个加入的数字是排名
//相当于根据集合里的元素的值  将集合拆分开
void outerAdd(int jobl, int jobr, int jobv, int l, int r, int i) {
    root[i] = innerAdd(jobl, jobr, 1, n, root[i]);
    if (l < r) {
        int mid = (l + r) >> 1;
        if (jobv <= mid) {
            outerAdd(jobl, jobr, jobv, l, mid, i << 1);
        } else {
            outerAdd(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
    }
}

//查询从jobl到jobr集合中  第jobk大的数字是什么  （实际上返回的是这个数字的排名）
//这个jobl和jobr实际上是内部集合的范围  l r是外部范围
int outerQuery(int jobl, int jobr, long long jobk, int l, int r, int i) {
    if (l == r) {
        return l;
    }
    int mid = (l + r) >> 1;
    long long rightsum = innerQuery(jobl, jobr, 1, n, root[i << 1 | 1]);
    if (jobk > rightsum) {
        return outerQuery(jobl, jobr, jobk - rightsum, l, mid, i << 1);
    } else {
        return outerQuery(jobl, jobr, jobk, mid + 1, r, i << 1 | 1);
    }
}

void prepare() {
    s = 0;
    for (int i = 1; i <= m; i++) {
        if (ques[i][0] == 1) {
            sorted[++s] = ques[i][3];
        }
    }
    sort(sorted + 1, sorted + s + 1);
    int len = 1;
    for (int i = 2; i <= s; i++) {
        if (sorted[len] != sorted[i]) {
            sorted[++len] = sorted[i];
        }
    }
    s = len;
    for (int i = 1; i <= m; i++) {
        if (ques[i][0] == 1) {
            ques[i][3] = kth(ques[i][3]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> ques[i][0] >> ques[i][1] >> ques[i][2] >> ques[i][3];
    }
    prepare();
    for (int i = 1; i <= m; i++) {
        if (ques[i][0] == 1) {
            outerAdd(ques[i][1], ques[i][2], ques[i][3], 1, s, 1);
            //加入一个大小为 ques[i][3]到集合ques[i][1]~ques[i][2]
        } else {
            int idx = outerQuery(ques[i][1], ques[i][2], ques[i][3], 1, s, 1);
            cout << sorted[idx] << "\n";
        }
    }
    return 0;
}
