#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
const int MAXM = 5005;

auto compare = [](const pair<int, int>& left, const pair<int, int>& right) {
    return left.second > right.second; // 注意这里是大于，因为我们想要小根堆
};

priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> heap(compare);
//初始化建立小根堆
vector<vector<pair<int ,int >>>graph;
//邻接表建图
int edge[MAXM][3];
int Distance[MAXN];
//记录到源点的最小距离
bool visit[MAXN];
//记录这个点是否被访问过
int n,m,s;

int main()
{
    cin>>n>>m>>s;
    graph.resize(n+1);
    for(int i=1;i<=m;i++){
        cin>>edge[i][0]>>edge[i][1]>>edge[i][2];
        graph[edge[i][0]].push_back({edge[i][1],edge[i][2]});
    }
    //初始化建图

    for(int i=1;i<=n;i++){
        Distance[i]=1e9;
    }
    //将数组初始化

    Distance[s]=0;
    //以s点作为源点传输信号
    heap.push({s,0});
    //小根堆储存的形式是  节点——权值  以权值建堆
    while(!heap.empty()){
        int u=heap.top().first;
        heap.pop();
        if(visit[u]){
            continue;
        }
        visit[u]=true;
        for(int i=0;i<graph[u].size();i++){
            int v=graph[u][i].first;
            int w=graph[u][i].second;
            if(!visit[v]&&(w+Distance[u])<Distance[v]){
                Distance[v]=w+Distance[u];
                heap.push({v,Distance[u]+w});
            }
        }
    }

    int ans=0;
    for(int i=1;i<=n;i++){
        if(Distance[i]==1e9){
            //表示无法到达
            cout<<-1;
            return 0;
        }
        ans=max(ans,Distance[i]);
        //取最大值  表示最远到达的点距离
    }
    cout<<ans;
    return 0;
}

