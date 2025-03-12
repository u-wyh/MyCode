// 货车运输
// 一共有n座城市，编号1 ~ n
// 一共有m条双向道路，每条道路(u, v, w)表示有一条限重为w，从u到v的双向道路
// 从一点到另一点的路途中，汽车载重不能超过每一条道路的限重
// 每条查询(a, b)表示从a到b的路线中，汽车允许的最大载重是多少
// 如果从a到b无法到达，那么认为答案是-1
// 一共有q条查询，返回答案数组
// 1 <= n <= 10^4
// 1 <= m <= 5 * 10^4
// 1 <= q <= 3 * 10^4
// 0 <= w <= 10^5
// 1 <= u, v, a, b <= n
// 测试链接 : https://www.luogu.com.cn/problem/P1967
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 10001;
const int MAXM = 50001;
const int LIMIT = 21;

int power;
struct node{
    int u,v,w;
}edge[MAXM];
//一开始不要直接建图  要建最大生成树
// 并查集
int father[MAXN];
// 给的树有可能是森林，所以需要判断节点是否访问过了
bool visited[MAXN];
// 最大生成树建图
int head[MAXN];
int Next[MAXM << 1];
int to[MAXM << 1];
int weight[MAXM << 1];
int cnt=1;
int deep[MAXN];
// stjump[u][p] : u节点往上跳2的次方步，到达什么节点
int stjump[MAXN][LIMIT];
// stmin[u][p] : u节点往上跳2的次方步的路径中，最小的权值
int stmin[MAXN][LIMIT];
int n,m,q;

void build() {
    power = log2(n);
    cnt = 1;
    for (int i = 1; i <= n; i++) {
        father[i] = i;
    }
}
//初始化并查集

bool cmp(node a,node b){
    return a.w>b.w;
}

int find(int i) {
    if (i != father[i]) {
        father[i] = find(father[i]);
    }
    return father[i];
}

void addEdge(int u, int v, int w) {
    Next[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

void kruskal() {
    sort(edge+1, edge+ m + 1, cmp);
    for (int i = 1, a, b, fa, fb; i <= m; i++) {
        a = edge[i].u;
        b = edge[i].v;
        fa = find(a);
        fb = find(b);
        if (fa != fb) {
            father[fa] = fb;
            addEdge(a, b, edge[i].w);
            addEdge(b, a, edge[i].w);
        }
    }
}
//使用k算法生成最大生成树

void dfs(int u, int w, int f) {
    //w是uf的边权  并且一定是最大的   因为经过了最大生成树
    visited[u] = true;
    if (f == 0) {
        deep[u] = 1;
        stjump[u][0] = u;
        stmin[u][0] = INT_MAX;
    } else {
        deep[u] = deep[f] + 1;
        stjump[u][0] = f;
        stmin[u][0] = w;
    }
    for (int p = 1; p <= power; p++) {
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
        stmin[u][p] = min(stmin[u][p - 1], stmin[stjump[u][p - 1]][p - 1]);
    }
    for (int e = head[u]; e != 0; e = Next[e]) {
        if (!visited[to[e]]) {
            dfs(to[e], weight[e], u);
        }
    }
}

int lca(int a, int b) {
    if (find(a) != find(b)) {
        return -1;
    }
    if (deep[a] < deep[b]) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    int ans = INT_MAX;
    for (int p = power; p >= 0; p--) {
        if (deep[stjump[a][p]] >= deep[b]) {
            ans = min(ans, stmin[a][p]);
            a = stjump[a][p];
        }
    }
    if (a == b) {
        return ans;
    }
    for (int p = power; p >= 0; p--) {
        if (stjump[a][p] != stjump[b][p]) {
            ans = min(ans, min(stmin[a][p], stmin[b][p]));
            a = stjump[a][p];
            b = stjump[b][p];
        }
    }
    ans =min(ans,min(stmin[a][0], stmin[b][0]));
    return ans;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>edge[i].u>>edge[i].v>>edge[i].w;
    }
    build();
    kruskal();
    //因为这道题上可能有不止一个集团  即不能通过一个方式实现建图
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i, 0, 0);
            //将每个集团建立一个st  deep
        }
    }
    cin>>q;
    for (int i = 1, a, b; i <= q; i++) {
        cin>>a>>b;
        cout<<lca(a, b)<<endl;;
    }
    return 0;
}
