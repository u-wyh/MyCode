//P4644
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 90000;
const int MAXM = 10005;

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
int n,st,en;

signed main()
{
    cin>>n>>st>>en;
    en++;
    int over=en;
    graph.resize(90005);
    for(int i=st;i<=en;i++){
        graph[i+1].push_back({i,0});
        //这里非常妙  即将所有的点连接  也不会影响权值
    }
    for(int i=1;i<=n;i++){
        cin>>edge[i][0]>>edge[i][1]>>edge[i][2];
        edge[i][1]++;
        over=max(over,edge[i][1]);
        graph[edge[i][0]].push_back({edge[i][1],edge[i][2]});
        if(edge[i][0]<st&&edge[i][1]>=st){
            //cout<<666<<endl;
            graph[st].push_back({edge[i][0],0});
        }
        if(edge[i][1]>en&&edge[i][0]<en){
            //cout<<777<<endl;
            graph[edge[i][1]].push_back({en,0});
        }
    }

    for(int i=0;i<=over;i++){
        Distance[i]=LLONG_MAX;
    }
    //将数组初始化

    Distance[st]=0;
    //以s点作为源点传输信号
    heap.push({st,0});
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

    if(Distance[en]==LLONG_MAX){
        cout<<-1<<endl;
        return 0;
    }
    cout<<Distance[en];
    return 0;
}

