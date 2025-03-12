// Bellman-Ford + SPFA优化模版（洛谷）
// 给定n个点的有向图，请求出图中是否存在从顶点1出发能到达的负环
// 负环的定义是：一条边权之和为负数的回路
// 测试链接 : https://www.luogu.com.cn/problem/P3385
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下所有代码，把主类名改成Main，可以直接通过
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2001;
const int MAXM = 6001;
// SPFA需要
const int MAXQ = 4000001;

// 链式前向星建图需要
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;
int n,m;
//n表示一共有多少个点  m表示一共有多少条路线
// 源点出发到每个节点的距离表
int dis[MAXN];
// 节点被松弛的次数
int updateCnt[MAXN];
bool enter[MAXN];
//当前在队列中的话  就是true  否则就是false
queue<int >q;
//每一轮都弹出最后面的一个  如果一个点可以被优化  那么加入队列

void build() {
    cnt = 1;
    fill(head+1, head+n + 1, 0);
    fill(enter+1,enter+ n + 1, false);
    fill(dis+ 1,dis+ n + 1, INT_MAX);
    fill(updateCnt+1,updateCnt+ n + 1, 0);
    while(!q.empty()){
        q.pop();
    }
}

void addEdge(int u, int v, int w) {
    Next[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}
//建立链式前向星

bool spfa() {
    dis[1] = 0;
    updateCnt[1]++;
    q.push(1) ;
    enter[1] = true;
    //这道题目中的源点都是1 保持不变   所以以上的操作都针对1
    //实际上应该理解为是针对源点的
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        enter[u] = false;
        for (int ei = head[u], v, w; ei > 0; ei = Next[ei]) {
            v = to[ei];
            w = weight[ei];
            if (dis[u] + w < dis[v]) {
                //如果值变小了  那么就要改变
                dis[v] = dis[u] + w;
                if (!enter[v]) {
                    //如果不在队列中才会加入
                    // 松弛次数超过n-1就有负环
                    if (++updateCnt[v] > n - 1) {
                        return true;
                    }
                    q.push(v);
                    enter[v] = true;
                }
            }
        }
    }
    return false;
}
//这个函数结束后  可以得到这个点到任何位置的最短路径
//这个函数是为了判断这个图中有没有从原点出发经过的负环

int main()
{
    int t;
    cin>>t;
    while(t--){
        cin>>n>>m;
        build();
        for(int i=1;i<=m;i++){
            int u,v,w;
            cin>>u>>v>>w;
            if (w >= 0) {
                addEdge(u, v, w);
                addEdge(v, u, w);
            } else {
                addEdge(u, v, w);
            }
            //根据题目要求建图
        }

        if(spfa()){
            cout<<"YES\n";
        }else{
            cout<<"NO\n";
        }
    }
    return 0;
}
