#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e3+5;
const int MAXM = 2e4+5;

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
    dis[0] = 0;
    updateCnt[0]++;
    q.push(0) ;
    enter[0] = true;
    //这道题目中的源点都是0 保持不变   所以以上的操作都针对1
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
                    if (++updateCnt[v] > n) {
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

int main()
{
    cin>>n>>m;
    build();
    for(int i=1;i<=n;i++){
        addEdge(0,i,0);
    }
    for(int i=1;i<=m;i++){
        int op;
        cin>>op;
        if(op==1){
            int u,v,w;
            cin>>u>>v>>w;
            addEdge(u,v,-w);
        }
        else if(op==2){
            int u,v,w;
            cin>>u>>v>>w;
            addEdge(v,u,w);
        }
        else{
            int u,v;
            cin>>u>>v;
            addEdge(u,v,0);
            addEdge(v,u,0);
        }
    }
    if(spfa()){
        cout<<"No"<<endl;
    }else{
        cout<<"Yes"<<endl;
    }
    return 0;
}
