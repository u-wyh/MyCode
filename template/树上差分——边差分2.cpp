// 运输计划(迭代版)
// 有n个节点，给定n-1条边使其连接成一棵树，每条边有正数边权
// 给定很多运输计划，每个运输计划(a,b)表示从a去往b
// 每个运输计划的代价就是沿途边权和，运输计划之间完全互不干扰
// 你只能选择一条边，将其边权变成0
// 你的目的是让所有运输计划代价的最大值尽量小
// 返回所有运输计划代价的最大值最小能是多少
// 测试链接 : https://www.luogu.com.cn/problem/P2680
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有用例
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 300001;
const int MAXM = 300001;

int n,m;

// num[i] : i节点和其父节点的边，有多少代价>=limit的运输计划用到
int num[MAXN];

// 链式前向星建图需要
int headEdge[MAXN];
int edgeNext[MAXN << 1];
int edgeTo[MAXN << 1];
int edgeWeight[MAXN << 1];
int tcnt=1;

// tarjan算法需要
int headQuery[MAXN];
int queryNext[MAXM << 1];
int queryTo[MAXM << 1];
int queryIndex[MAXM << 1];
int qcnt=1;

bool visited[MAXN];
int unionfind[MAXN];
int quesu[MAXM];
int quesv[MAXM];

// distance[i] : 头节点到i号点的距离，tarjan算法过程中更新
int dis[MAXN];
// lca[i] : 第i号运输计划的两端点lca，tarjan算法过程中更新
int lca[MAXM];
// cost[i] : 第i号运输计划代价是多少，tarjan算法过程中更新
int cost[MAXM];
// 所有运输计划的最大代价，tarjan算法过程中更新
int maxCost;
// 至少要减少多少边权
int atLeast;
// 超过要求的运输计划有几个
int beyond;

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

void addEdge(int u, int v, int w) {
    edgeNext[tcnt] = headEdge[u];
    edgeTo[tcnt] = v;
    edgeWeight[tcnt] = w;
    headEdge[u] = tcnt++;
}

void addQuery(int u, int v, int i) {
    queryNext[qcnt] = headQuery[u];
    queryTo[qcnt] = v;
    queryIndex[qcnt] = i;
    headQuery[u] = qcnt++;
}

int find(int i) {
    if (i != unionfind[i]) {
        unionfind[i] = find(unionfind[i]);
    }
    return unionfind[i];
}

void tarjan(int u, int f, int w) {
    visited[u] = true;
    dis[u] = dis[f] + w;
    for (int e = headEdge[u], v; e != 0; e = edgeNext[e]) {
        v = edgeTo[e];
        if (v != f) {
            tarjan(v, u, edgeWeight[e]);
        }
    }
    for (int e = headQuery[u], v, i; e != 0; e = queryNext[e]) {
        v = queryTo[e];
        if (visited[v]) {
            i = queryIndex[e];
            lca[i] = find(v);
            cost[i] = dis[u] + dis[v] - 2 * dis[lca[i]];
            maxCost = max(maxCost, cost[i]);
        }
    }
    unionfind[u] = f;
}

bool dfs(int u, int f, int w) {
    for (int e = headEdge[u], v; e != 0; e = edgeNext[e]) {
        v = edgeTo[e];
        if (v != f) {
            if (dfs(v, u, edgeWeight[e])) {
                return true;
            }
        }
    }
    for (int e = headEdge[u], v; e != 0; e = edgeNext[e]) {
        v = edgeTo[e];
        if (v != f) {
            num[u] += num[v];
        }
    }
    return num[u] == beyond && w >= atLeast;
}

// 只能把一条边的权值变成0
// 还要求每个运输计划的代价都要<=limit
// 返回能不能做到
bool f(int limit) {
	atLeast = maxCost - limit;
	for(int i=1;i<=n;i++){
        num[i]=0;
	}
	beyond = 0;
	for (int i = 1; i <= m; i++) {
		if (cost[i] > limit) {
			num[quesu[i]]++;
			num[quesv[i]]++;
			num[lca[i]] -= 2;
			beyond++;
		}
	}
	return beyond == 0 || dfs(1, 0, 0);
}

int compute() {
    tarjan(1, 0, 0);
    int l = 0, r = maxCost, mid;
    int ans = 0;
    while (l <= r) {
        mid = (l + r) / 2;
        if (f(mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}

int main()
{
    n=read(),m=read();
    for (int i = 1; i <= n; i++) {
        unionfind[i] = i;
    }
    for(int i=1,u,v,w;i<n;i++){
        u=read(),v=read(),w=read();
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    for(int i=1,u,v;i<=m;i++){
        u=read(),v=read();
        quesu[i]=u;
        quesv[i]=v;
        addQuery(u,v,i);
        addQuery(v,u,i);
    }
    cout<<compute()<<endl;
    return 0;
}
