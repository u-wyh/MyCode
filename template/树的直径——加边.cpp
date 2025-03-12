// 巡逻
// 一共n个节点，编号1~n，结构是一棵树，每条边都是双向的
// 警察局在1号点，警车每天从1号点出发，一定要走过树上所有的边，最后回到1号点
// 现在为了减少经过边的数量，你可以新建k条边，把树上任意两点直接相连
// 并且每天警车必须经过新建的道路正好一次
// 计算出最佳的新建道路的方案，返回巡逻走边数量的最小值
// 测试链接 : https://www.luogu.com.cn/problem/P3629
// 1 <= n <= 10^5
// 1 <= k <= 2
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有用例
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100001;

int n,k;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt=1;
// 直径的开始点
int start;
// 直径的结束点
int en;
// 直径长度
int diameter1,diameter2;
// dist[i] : 从规定的头节点出发，走到i的距离
int dist[MAXN];
// last[i] : 从规定的头节点出发，i节点的上一个节点
int last[MAXN];
bool diameterPath[MAXN];

void dfs(int u,int f,int w){
    last[u]=f;
    dist[u]=dist[f]+w;
    for(int i=head[u];i>0;i=Next[i]){
        if(to[i]!=f){
            dfs(to[i],u,1);
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
    diameter1 = dist[en];
}
//两次调用dfs

void dp(int u, int f) {
    for (int e = head[u], v; e != 0; e = Next[e]) {
        v = to[e];
        if (v != f) {
            dp(v, u);
        }
    }
    for (int e = head[u], v, w; e != 0; e = Next[e]) {
        v = to[e];
        if (v != f) {
            w = diameterPath[u] && diameterPath[v] ? -1 : 1;
            //如果这两个节点都是true  那么这条路的权值就是-1
            diameter2 = max(diameter2, dist[u] + dist[v] + w);
            dist[u] = max(dist[u], dist[v] + w);
        }
    }
}

int main()
{
    cin>>n>>k;
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
    road();
    //这个函数只能完成diameter1的大小测量
    if(k==1){
        //只加一条边的情况
        //只会节约这条直径上的节点个数
        cout<<2*(n-1)-diameter1+1;
    }else{
        for(int i=en;i!=0;i=last[i]){
            diameterPath[i]=true;
        }
        //将直径上的节点标记为true
        for(int i=1;i<=n;i++){
            dist[i]=0;
        }
        //全部完成初始化
        dp(1,0);
        //得到diameter2的大小  其中diameter2是除去和直径的公共边的结点个数
        cout<<2*(n-1)-diameter1-diameter2+2;
    }
    return 0;
}
