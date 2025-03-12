// 消防(递归版)
// 一共n个节点，编号1~n，有n-1条边连接成一棵树，每条边上有非负权值
// 给定一个非负整数s，表示可以在树上选择一条长度不超过s的路径
// 然后在这条路径的点上建立消防站，每个居民可以去往这条路径上的任何消防站
// 目标：哪怕最远的居民走到消防站的距离也要尽量少
// 返回最远居民走到消防站的最短距离
// 测试链接 : https://www.luogu.com.cn/problem/P2491
// 提交以下的code，提交时请把类名改成"Main"
// C++这么写能通过，java会因为递归层数太多而爆栈
// java能通过的写法参考本节课Code05_FireFighting2文件

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 300005;

int n,s;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;
// 直径的开始点
int start;
// 直径的结束点
int en;
// 直径长度
int diameter;
// dist[i] : 从规定的头节点出发，走到i的距离
int dist[MAXN];
// last[i] : 从规定的头节点出发，i节点的上一个节点
int last[MAXN];
bool diameterPath[MAXN];
int maxDist[MAXN];
int pred[MAXN];
// pred[i] : i节点在直径上，和前一个点之间的距离，以start做根

void dfs(int u,int f,int w){
    last[u]=f;
    dist[u]=dist[f]+w;
    pred[u]=w;
    for(int i=head[u];i>0;i=Next[i]){
        if(to[i]!=f){
            dfs(to[i],u,weight[i]);
        }
    }
}

int maxDistanceExceptDiameter(int u, int f, int c) {
    int ans = c;
    for (int e = head[u], v; e != 0; e = Next[e]) {
        v = to[e];
        if (!diameterPath[v] && v != f) {
            ans = max(ans, maxDistanceExceptDiameter(v, u, c + weight[e]));
        }
    }
    return ans;
}
//在路径上的点不走直径上的点可以到的最远距离

void distance() {
    for (int i = en; i != 0; i = last[i]) {
        diameterPath[i] = true;
    }
    for (int i = en; i != 0; i = last[i]) {
        maxDist[i] = maxDistanceExceptDiameter(i, 0, 0);
    }
}

void road() {
    dfs(1, 0, 0);
    //这个起点是随机的  一般都是1
    start = 1;
    for (int i = 2; i <= n; i++) {
        if (dist[i] > dist[start]) {
            start = i;
        }
    }
    //选择离他距离最大的点  作为头结点
    dfs(start, 0, 0);
    en = 1;
    for (int i = 2; i <= n; i++) {
        if (dist[i] > dist[en]) {
            en = i;
        }
    }
    diameter = dist[en];
}
//两次调用dfs

int Queue[MAXN];

int compute() {
    int suml = 0, sumr = 0;
    // 用h和t表示单调队列的头和尾
    int h = 0, t = 0;
    int ans = INT_MAX;
    // 窗口范围[l,r)，左闭右开，直径上的窗口[l...r-1]
    // l是窗口左端点，r是窗口右端点的再下一个点
    // 课上图解是从start到end，实际是从end到start，思路没有区别
    for (int l = en, r = en; l != 0; l = last[l]) {
        while (r != 0 && sumr - suml + pred[r] <= s) {
            while (h < t && maxDist[Queue[t - 1]] <= maxDist[r]) {
                t--;
            }
            sumr += pred[r];
            Queue[t++] = r;
            r = last[r];
        }
        ans = min(ans, max(max(suml, maxDist[Queue[h]]), diameter - sumr));
        if (Queue[h] == l) {
            h++;
        }
        suml += pred[l];
    }
    return ans;
}

int main()
{
    cin>>n>>s;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;

        Next[cnt]=head[u];
        to[cnt]=v;
        weight[cnt]=w;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        weight[cnt]=w;
        head[v]=cnt++;
    }
    road();
    distance();
    cout<<compute();
    return 0;
}
