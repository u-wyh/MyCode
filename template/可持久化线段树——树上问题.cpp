// 路径上的第k小，java版
// 有n个节点，编号1~n，每个节点有权值，有n-1条边，所有节点组成一棵树
// 一共有m条查询，每条查询 u v k : 打印u号点到v号点的路径上，第k小的点权
// 题目有强制在线的要求，上一次打印的答案为lastAns，初始时lastAns = 0
// 每次给定的u、v、k，按照如下方式得到真实的u、v、k，查询完成后更新lastAns
// 真实u = 给定u ^ lastAns
// 真实v = 给定v
// 真实k = 给定k
// 1 <= n、m <= 10^5
// 1 <= arr[i] <= 2^32 - 1
// 测试链接 : https://www.luogu.com.cn/problem/P2633
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100001;
const int MAXH = 20;
const int MAXT = MAXN * MAXH;

int n, m, s;
// 各个节点权值
int arr[MAXN];
// 收集权值排序并且去重做离散化
int sorted[MAXN];

// 链式前向星需要
int head[MAXN];
int to[MAXN << 1];
int Next[MAXN << 1];
int cntg = 1;

// 可持久化线段树需要
int root[MAXN];
int ls[MAXT];
int rs[MAXT];
int sz[MAXT];
int cntt = 0;

// 树上倍增找lca需要
int deep[MAXN];
int stjump[MAXN][MAXH];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

void addedge(int u,int v){
    Next[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

//二分查找
int kth(int num) {
    int left = 1, right = s, mid;
    while (left <= right) {
        mid = (left + right) / 2;
        if (sorted[mid] == num) {
            return mid;
        } else if (sorted[mid] < num) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int build(int l, int r) {
    int rt = ++cntt;
    sz[rt] = 0;
    if (l < r) {
        int mid = (l + r) / 2;
        ls[rt] = build(l, mid);
        rs[rt] = build(mid + 1, r);
    }
    return rt;
}

void prepare(){
    for(int i=1;i<=n;i++){
        sorted[i]=arr[i];
    }
    sort(sorted+1,sorted+n+1);
    s=1;
    for(int i=2;i<=n;i++){
        if(sorted[i]!=sorted[i-1]){
            sorted[++s]=sorted[i];
        }
    }
    //排序并离散化
    root[0]=build(1,s);
}

int insert(int jobi, int l, int r, int i) {
    int rt = ++cntt;
    ls[rt] = ls[i];
    rs[rt] = rs[i];
    sz[rt] = sz[i] + 1;
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

//dfs建立可持久化线段树  每次插入一个元素
//在此过程中  同时完成st表
void dfs1(int u, int f) {
    root[u] = insert(kth(arr[u]), 1, s, root[f]);
    deep[u] = deep[f] + 1;
    stjump[u][0] = f;
    for (int p = 1; p < MAXH; p++) {
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
    }
    for (int ei = head[u]; ei > 0; ei = Next[ei]) {
        if (to[ei] != f) {
            dfs1(to[ei], u);
        }
    }
}

int query(int jobk, int l, int r, int u, int v, int lca, int lcafa) {
    if (l == r) {
        return l;
    }
    int lsize = sz[ls[u]] + sz[ls[v]] - sz[ls[lca]] - sz[ls[lcafa]];
    int mid = (l + r) / 2;
    if (lsize >= jobk) {
        return query(jobk, l, mid, ls[u], ls[v], ls[lca], ls[lcafa]);
    } else {
        return query(jobk - lsize, mid + 1, r, rs[u], rs[v], rs[lca], rs[lcafa]);
    }
}

int lca(int a, int b) {
    if (deep[a] < deep[b]) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    for (int p = MAXH - 1; p >= 0; p--) {
        if (deep[stjump[a][p]] >= deep[b]) {
            a = stjump[a][p];
        }
    }
    if (a == b) {
        return a;
    }
    for (int p = MAXH - 1; p >= 0; p--) {
        if (stjump[a][p] != stjump[b][p]) {
            a = stjump[a][p];
            b = stjump[b][p];
        }
    }
    return stjump[a][0];
}

int kth(int u, int v, int k) {
    int Lca = lca(u, v);//相当于是树上差分
    int i = query(k, 1, s, root[u], root[v], root[Lca], root[stjump[Lca][0]]);
    return sorted[i];
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
    }
    prepare();
    for(int i=1,u,v;i<n;i++){
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    dfs1(1,0);//通过深度优先搜索实现遍历  和建可持久化树
    for(int i=1,u,v,k,lastans=0;i<=m;i++){
        u=read(),v=read(),k=read();
        u^=lastans;
        lastans=kth(u,v,k);
        cout<<lastans<<endl;
    }
    return 0;
}
