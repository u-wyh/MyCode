// 删增边使其重心唯一
// 一共有n个节点，编号1~n，有n-1条边形成一棵树
// 现在希望重心是唯一的节点，调整的方式是先删除一条边、然后增加一条边
// 如果树上只有一个重心，需要删掉连接重心的任意一条边，再把这条边加上(否则无法通过已经实测)
// 如果树上有两个重心，调整的方式是先删除一条边、然后增加一条边，使重心是唯一的
// 如果方案有多种，打印其中一种即可
// 比如先删除节点3和节点4之间的边，再增加节点4和节点7之间的边，那么打印:
// "3 4"
// "4 7"
// 测试链接 : https://www.luogu.com.cn/problem/CF1406C
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有用例
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 100001;

int n;
int head[MAXN];
int Next[MAXN << 1];
int to[MAXN << 1];
int cnt;

// size[i] : 从1号节点开始dfs的过程中，以i为头的子树的节点数
int sz[MAXN];

// maxsub[i] : 如果节点i做整棵树的根，最大子树的大小
int maxsub[MAXN];

// 收集所有的重心
vector<int> centers;

// 任何一个叶节点
int anyLeaf;

// 该叶节点的父亲节点
int anyLeafFather;

void build() {
    cnt = 1;
    fill(head + 1, head + n + 1, 0);
}

void addEdge(int u, int v) {
    Next[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

void dfs(int u, int f) {
    sz[u] = 1;
    maxsub[u] = 0;
    for (int e = head[u]; e != 0; e = Next[e]) {
        int v = to[e];
        if (v != f) {
            dfs(v, u);
            sz[u] += sz[v];
            maxsub[u] = max(maxsub[u], sz[v]);
        }
    }
    maxsub[u] = max(maxsub[u], n - sz[u]);
}

// 随意找一个叶节点和该叶节点的父亲节点
void find(int u, int f) {
    for (int e = head[u]; e != 0; e = Next[e]) {
        int v = to[e];
        if (v != f) {
            find(v, u);
            return;
        }
    }
    anyLeaf = u;
    anyLeafFather = f;
}

int compute() {
    dfs(1, 0);
    centers.clear();
    for (int i = 1; i <= n; i++) {
        if (maxsub[i] <= n / 2) {
            centers.push_back(i);
        }
    }
    if (centers.size() == 2) {
        find(centers[1], centers[0]);
        //如果有两个重心  那么他们必然相邻  使之为父子关系
        //找到一个centers[1]的叶子节点 将这个节点挂到centers[0]上即可
    }
    return centers.size();
}

int main() {
    int testCase;
    scanf("%d", &testCase);
    for (int t = 1; t <= testCase; t++) {
        scanf("%d", &n);
        build();
        for (int i = 1, u, v; i < n; i++) {
            scanf("%d%d", &u, &v);
            addEdge(u, v);
            addEdge(v, u);
        }
        int centroidCount = compute();
        if (centroidCount == 1) {
            int centroid = centers[0];
            int neighbor = to[head[centroid]]; // 假设这里取第一个邻接点作为输出（注意可能有多个）
            printf("%d %d\n", centroid, neighbor);
            printf("%d %d\n", centroid, neighbor); // 根据题目要求，可能需要输出不同的边
            // 注意：这里假设只需要输出任意一条与重心相连的边，实际情况可能需要根据题目要求调整
        } else {
            printf("%d %d\n", anyLeafFather, anyLeaf);
            printf("%d %d\n", centers[0], anyLeaf);
        }
    }
    return 0;
}
