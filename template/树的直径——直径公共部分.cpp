// 所有直径的公共部分(递归版)
// 给定一棵树，边权都为正
// 打印直径长度、所有直径的公共部分有几条边
// 测试链接 : https://www.luogu.com.cn/problem/P3304
// 提交以下的code，提交时请把类名改成"Main"
// C++这么写能通过，java会因为递归层数太多而爆栈
// java能通过的写法参考本节课Code02_DiameterAndCommonEdges2文件

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 200005;

int n;
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
long diameter;
// dist[i] : 从规定的头节点出发，走到i的距离
long dist[MAXN];
// last[i] : 从规定的头节点出发，i节点的上一个节点
int last[MAXN];
bool diameterPath[MAXN];
//是否是直径上的点(只有一条直径上改为true即可)
int commonEdges;
//公共点数

void dfs(int u,int f,long w){
    last[u]=f;
    dist[u]=dist[f]+w;
    for(int i=head[u];i>0;i=Next[i]){
        if(to[i]!=f){
            dfs(to[i],u,weight[i]);
        }
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
//两次调用dfs   找到直径大小

long maxDistanceExceptDiameter(int u, int f, long c) {
    long ans = c;
    for (int e = head[u], v; e != 0; e = Next[e]) {
        v = to[e];
        if (!diameterPath[v] && v != f) {
            ans = max(ans, maxDistanceExceptDiameter(v, u, c + weight[e]));
        }
    }
    return ans;
}
//在路径上的点不走直径上的点可以到的最远距离

void compute() {
    road();
    for (int i = en; i != 0; i = last[i]) {
        diameterPath[i] = true;
        //表示是在这一条直径上的点
    }
    int l = start;
    int r = en;
    long maxDist;
    for (int i = last[en]; i != start; i = last[i]) {
        maxDist = maxDistanceExceptDiameter(i, 0, 0);
        if (maxDist == diameter - dist[i]) {
            //表示到其他不在直径上的点距离和到最后点的距离一样
            //说明这个点是多条直径的公共点
            r = i;
        }
        //最后一个符合条件的右端点
        if (maxDist == dist[i] && l == start) {
            l = i;
        }
        //第一个符合条件的点  以后的不会符合l==start
    }
    if (l == r) {
        commonEdges = 0;
    } else {
        commonEdges = 1;
        for (int i = last[r]; i != l; i = last[i]) {
            commonEdges++;
        }
    }
}
//公共部分的最右边点的 maxDistanceExceptDiameter  一定等于到直径end的距离  从end开始找  最后一个符合条件的才是
//公共部分的最左边点的 maxDistanceExceptDiameter  一定等于到直径start的距离  从end开始找  第一个符合条件的才是
//并且最左边点一定在右边点左边

int main()
{
    cin>>n;
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
    //建图
    compute();
    cout<<diameter<<endl<<commonEdges;
    return 0;
}

