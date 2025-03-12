// 选择节点做根使流量和最大(递归版)
// 给定一棵n个点的树，边的边权代表流量限制
// 从边上流过的流量，不能超过流量限制
// 现在想知道以某个节点做根时，流到所有叶节点的流量，最大是多少
// 测试链接 : http://poj.org/problem?id=3585
// 提交以下的code，提交时请把类名改成"Main"
// C++这么写能通过，java会因为递归层数太多而爆栈
// java能通过的写法参考本节课Code04_MaximizeFlow2文件
#include<iostream>
#include<cmath>
#include<cstdio>
using namespace std;
const int MAXN = 200001;

int n;

int head[MAXN];
int to[MAXN<<1];
int weight[MAXN<<1];
int Next[MAXN<<1];
int cnt;

// degree[u] : 有几条边和u节点相连
int degree[MAXN];
// flow[u] : 从u出发流向u节点为头的子树上，所有的叶节点，流量是多少
int flow[MAXN];
// dp[u] : 从u出发流向u节点为根的整棵树上，所有的叶节点，流量是多少
int dp[MAXN];

void build() {
    cnt = 1;
    for(int i=1;i<=n;i++){
        head[i]=0;
        degree[i]=0;
        flow[i]=0;
        dp[i]=0;
    }
}

void addEdge(int u, int v, int w) {
    Next[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

void dfs1(int u, int f) {
    for (int e = head[u], v; e != 0; e = Next[e]) {
        v = to[e];
        if (v != f) {
            dfs1(v, u);
        }
    }
    for (int e = head[u], v; e != 0; e = Next[e]) {
        v = to[e];
        if (v != f) {
            if (degree[v] == 1) {
                flow[u] += weight[e];
            } else {
                flow[u] += min(flow[v], weight[e]);
            }
        }
    }
}

void dfs2(int u, int f) {
    for (int e = head[u], v; e != 0; e = Next[e]) {
        v = to[e];
        if (v != f) {
            if (degree[u] == 1) {
                dp[v] = flow[v] + weight[e];
            } else {
                // uOut : u流向外的流量
                int uOut = dp[u] - min(flow[v], weight[e]);
                dp[v] = flow[v] + min(uOut, weight[e]);
            }
            dfs2(v, u);
        }
    }
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        build();
        for(int i=1,u,v,w;i<n;i++){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
            degree[u]++;
            degree[v]++;
        }
        dfs1(1, 0);
        dp[1] = flow[1];
        dfs2(1, 0);
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            ans = max(ans, dp[i]);
        }
        printf("%d\n",ans);
    }

    return 0;
}
