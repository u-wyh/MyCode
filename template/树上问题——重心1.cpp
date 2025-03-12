// 哪些点可以改造成重心
// 给定一棵n个点的树，你可以随便删掉一条边，然后随便加上一条边
// 通过这种方式可以让很多点变成重心
// 打印所有能变成重心的点
// 测试链接 : https://www.luogu.com.cn/problem/CF708C
// 测试链接 : https://codeforces.com/problemset/problem/708/C
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有用例
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 4e5+5;

int n,k;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;

// size[i]: i内部，整棵子树大小
int sz[MAXN];
// maxsub[i]: i内部，最大子树，是i节点的哪个儿子拥有，记录节点编号
int maxsub[MAXN];
// inner1[i]: i内部，<=n/2且第一大的子树是多大，记录大小
int inner1[MAXN];
// inner2[i]: i内部，<=n/2且第二大的子树是多大，记录大小
int inner2[MAXN];
// 注意: inner1[i]和inner2[i]，所代表的子树一定要来自i的不同儿子

// choose[i]: inner1[i]所代表的子树，是i节点的哪个儿子拥有，记录节点编号
int choose[MAXN];
// outer[i]: i外部，<=n/2且第一大的子树是多大，记录大小
int outer[MAXN];

void dfs1(int u, int f) {
    sz[u] = 1;
    for (int e = head[u], v; e != 0; e = Next[e]) {
        v = to[e];
        if (v != f) {
            dfs1(v, u);
            sz[u] += sz[v];
            if (sz[maxsub[u]] < sz[v]) {
                maxsub[u] = v;
            }
            int innerSize = sz[v] <= n / 2 ? sz[v] : inner1[v];
            if (inner1[u] < innerSize) {
                choose[u] = v;
                inner2[u] = inner1[u];
                inner1[u] = innerSize;
            } else if (inner2[u] < innerSize) {
                inner2[u] = innerSize;
            }
        }
    }
}

void dfs2(int u, int f) {
    for (int e = head[u], v; e != 0; e = Next[e]) {
        v = to[e];
        if (v != f) {
            if (n - sz[v] <= n / 2) {
                outer[v] = n - sz[v];
            } else if (choose[u] != v) {
                outer[v] = max(outer[u], inner1[u]);
            } else {
                outer[v] = max(outer[u], inner2[u]);
            }
            dfs2(v, u);
        }
    }
}

bool check(int u) {
    if (sz[maxsub[u]] > n / 2) {
        //如果子树中存在大于n/2的子树  首先可以确定的是他的父亲们是正常的  一定小于n/2
        //那么我们要做的就是最大程度的削弱这颗最大子树大小  尽量使其合理
        //只可以断掉一条边  那么断的这条边会接到u上  即这条边要尽量大还要小于n/2
        //这就是inner1的定义
        return sz[maxsub[u]] - inner1[maxsub[u]] <= n / 2;
    }
    if (n - sz[u] > n / 2) {
        //道理同上
        return n - sz[u] - outer[u] <= n / 2;
    }
    //到了这里  说明根本没有大于n/2的子树  即本身就是重心
    return true;
}

int main()
{
    cin>>n;
        for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;

        Next[cnt]=head[u];
        to[cnt]=v;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        head[v]=cnt++;

    }
    dfs1(1,0);
    dfs2(1,0);
    for (int i = 1; i <= n; i++) {
        cout<<(check(i) ? "1 " : "0 ");
    }
    return 0;
}

