// 旅游，C++版
// 一共有n个城市，给定n-1条边，城市连成一棵树，每个城市给定初始的宝石价格
// 一共有m条操作，操作类型如下
// 操作 x y v : 城市x到城市y的最短路途中，你可以选择一城买入宝石
//              继续行进的过程中，再选一城卖出宝石，以此获得利润
//              打印你能获得的最大利润，如果为负数，打印0
//              当你结束旅途后，沿途所有城市的宝石价格增加v
// 1 <= n、m <= 5 * 10^4
// 0 <= 任何时候的宝石价格 <= 10^9
// 测试链接 : https://www.luogu.com.cn/problem/P3976
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 50001;
const int INF  = 1000000001;

int n, m;
int arr[MAXN];//初始时颜色种类

//链式前向星
int head[MAXN];
int nxt[MAXN << 1];
int to[MAXN << 1];
int cntg = 0;

//树链剖分
int fa[MAXN];
int dep[MAXN];
int siz[MAXN];
int son[MAXN];
int top[MAXN];
int dfn[MAXN];
int seg[MAXN];
int cntd = 0;

//线段树
int maxv[MAXN << 2];//区间最大值
int minv[MAXN << 2];//区间最小值
int lprofit[MAXN << 2];//由于有方向问题  这个是从左到右最大利润
int rprofit[MAXN << 2];//由于有方向问题  这个是从右到左最大利润
// 线段树范围增加的懒更新信息
int addTag[MAXN << 2];

void addEdge(int u, int v) {
    nxt[++cntg] = head[u];
    to[cntg] = v;
    head[u] = cntg;
}

void dfs1(int u, int f) {
    fa[u] = f;
    dep[u] = dep[f] + 1;
    siz[u] = 1;
    for (int e = head[u]; e > 0; e = nxt[e]) {
        int v = to[e];
        if (v != f) {
            dfs1(v, u);
        }
    }
    for (int e = head[u]; e > 0; e = nxt[e]) {
        int v = to[e];
        if (v != f) {
            siz[u] += siz[v];
            if (son[u] == 0 || siz[son[u]] < siz[v]) {
                son[u] = v;
            }
        }
    }
}

void dfs2(int u, int t) {
    top[u] = t;
    dfn[u] = ++cntd;
    seg[cntd] = u;
    if (son[u] == 0) {
        return;
    }
    dfs2(son[u], t);
    for (int e = head[u]; e > 0; e = nxt[e]) {
        int v = to[e];
        if (v != fa[u] && v != son[u]) {
            dfs2(v, v);
        }
    }
}

void up(int i) {
    int l = i << 1;
    int r = i << 1 | 1;
    maxv[i] = max(maxv[l], maxv[r]);
    minv[i] = min(minv[l], minv[r]);
    lprofit[i] = max({lprofit[l], lprofit[r], maxv[r] - minv[l]});
    rprofit[i] = max({rprofit[l], rprofit[r], maxv[l] - minv[r]});
}

void lazy(int i, int v) {
    maxv[i] += v;
    minv[i] += v;
    addTag[i] += v;
}

void down(int i) {
    if (addTag[i] != 0) {
        lazy(i << 1, addTag[i]);
        lazy(i << 1 | 1, addTag[i]);
        addTag[i] = 0;
    }
}

void build(int l, int r, int i) {
    if (l == r) {
        maxv[i] = minv[i] = arr[seg[l]];
    } else {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i);
    }
}

void add(int jobl, int jobr, int jobv, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        lazy(i, jobv);
    } else {
        down(i);
        int mid = (l + r) >> 1;
        if (jobl <= mid) {
            add(jobl, jobr, jobv, l, mid, i << 1);
        }
        if (jobr > mid) {
            add(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
        up(i);
    }
}

// ans[0] : 线段树更左侧部分的max
// ans[1] : 线段树更左侧部分的min
// ans[2] : 线段树更左侧部分的lprofit
// ans[3] : 线段树更左侧部分的rprofit
// rmax : 线段树更右侧部分的max
// rmin : 线段树更右侧部分的min
// rlpro : 线段树更右侧部分的lprofit
// rrpro : 线段树更右侧部分的rprofit
// 左侧部分和右侧部分的信息整合在一起得到整个范围的max、min、lprofit、rprofit
void merge(int ans[], int rmax, int rmin, int rlpro, int rrpro) {
    int lmax  = ans[0];
    int lmin  = ans[1];
    int llpro = ans[2];
    int lrpro = ans[3];
    ans[0] = max(lmax, rmax);
    ans[1] = min(lmin, rmin);
    ans[2] = max({llpro, rlpro, rmax - lmin});
    ans[3] = max({lrpro, rrpro, lmax - rmin});
    //和up函数的信息组合方式一样
}

void query(int ans[], int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        //将以前收集的信息和目前的信息合并  以前的信息肯定是左侧部分的信息
        merge(ans, maxv[i], minv[i], lprofit[i], rprofit[i]);
    } else {
        down(i);
        int mid = (l + r) >> 1;
        if (jobl <= mid) {
            query(ans, jobl, jobr, l, mid, i << 1);
        }
        if (jobr > mid) {
            query(ans, jobl, jobr, mid + 1, r, i << 1 | 1);
        }
    }
}

// ans[0] : 线段树更左侧部分的max
// ans[1] : 线段树更左侧部分的min
// ans[2] : 线段树更左侧部分的lprofit
// ans[3] : 线段树更左侧部分的rprofit
// 随着线段树查询的展开，会有更右部分的信息整合进ans，最终整合出整体信息
void query(int ans[], int jobl, int jobr) {
    ans[0] = -INF;
    ans[1] =  INF;
    ans[2] =  0;
    ans[3] =  0;
    //初始时将ans数组  最大值设置为较小值  最小值设置为较大值  左右利润都设置为0  方便后来覆盖
    query(ans, jobl, jobr, 1, n, 1);
}

void clone(int *a, int *b) {
    a[0] = b[0];
    a[1] = b[1];
    a[2] = b[2];
    a[3] = b[3];
}

int compute(int x, int y, int v) {
    int tmpx = x;
    int tmpy = y;
    int xpath[4] = {-INF, INF, 0, 0};//收集x到lca的信息
    int ypath[4] = {-INF, INF, 0, 0};//收集y到lca的信息
    int cur[4];
    while (top[x] != top[y]) {
        if (dep[top[x]] <= dep[top[y]]) {
            query(cur, dfn[top[y]], dfn[y]);//将查询的信息送到cur数组中
            merge(cur, ypath[0], ypath[1], ypath[2], ypath[3]);//将ypath的信息汇总到cur中  因为cur在左侧
            clone(ypath, cur);//再将cur信息送回到ypath
            y = fa[top[y]];
        } else {
            query(cur, dfn[top[x]], dfn[x]);
            merge(cur, xpath[0], xpath[1], xpath[2], xpath[3]);
            clone(xpath, cur);
            x = fa[top[x]];
        }
    }
    //根据节点的深度判断最后一段属于那一部分
    if (dep[x] <= dep[y]) {
        query(cur, dfn[x], dfn[y]);
        merge(cur, ypath[0], ypath[1], ypath[2], ypath[3]);
        clone(ypath, cur);
    } else {
        query(cur, dfn[y], dfn[x]);
        merge(cur, xpath[0], xpath[1], xpath[2], xpath[3]);
        clone(xpath, cur);
    }
    //实际上x到lca是从右到左的过程  lca到y是从左到右
    int ans = max({xpath[3], ypath[2], ypath[0] - xpath[1]});

    //将区间上的权值按照题目要求加上v
    x = tmpx;
    y = tmpy;
    while (top[x] != top[y]) {
        if (dep[top[x]] <= dep[top[y]]) {
            add(dfn[top[y]], dfn[y], v, 1, n, 1);
            y = fa[top[y]];
        } else {
            add(dfn[top[x]], dfn[x], v, 1, n, 1);
            x = fa[top[x]];
        }
    }
    add(min(dfn[x], dfn[y]), max(dfn[x], dfn[y]), v, 1, n, 1);
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    build(1, n, 1);
    cin >> m;
    for (int i = 1; i <= m; i++) {
        int x, y, v;
        cin >> x >> y >> v;
        cout << compute(x, y, v) << "\n";
    }
    return 0;
}
