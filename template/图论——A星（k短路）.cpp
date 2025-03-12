//P2901
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
const int MAXM = 10005;
const int MAXT = 105;

int n,m,k;
int ans[MAXT];
int tot;

int dis[MAXN];//这是求节点1到各个节点的距离  用于A*
bool vis[MAXN];

int head[MAXN];
int Next[MAXM];
int weight[MAXM];
int to[MAXM];
int cnt=1;

//反图系列
int head1[MAXN];
int Next1[MAXM];
int weight1[MAXM];
int to1[MAXM];
int cnt1=1;

void addedge(int u,int v,int w){
    Next[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void Addedge(int u,int v,int w){
    Next1[cnt1]=head1[u];
    to1[cnt1]=v;
    weight1[cnt1]=w;
    head1[u]=cnt1++;
}

auto compare = [](const pair<int, int>& left, const pair<int, int>& right) {
    return left.second > right.second; // 注意这里是大于，因为我们想要小根堆
};
priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> heap(compare);

void dijkstra(){
    for(int i=1;i<=n;i++){
        dis[i]=INT_MAX;
    }
    dis[1]=0;
    heap.push({1,0});
    while(!heap.empty()){
        int u=heap.top().first;
        heap.pop();
        if(vis[u]){
            continue;
        }
        vis[u]=true;
        for(int i=head1[u];i;i=Next1[i]){
            int v=to1[i];
            int w=weight1[i];
            if(!vis[v]&&(w+dis[u])<dis[v]){
                dis[v]=w+dis[u];
                heap.push({v,dis[u]+w});
            }
        }
    }
}

auto cmp = [](const pair<int, int>& left, const pair<int, int>& right) {
    return left.second+dis[left.first] > right.second+dis[right.first]; // 注意这里是大于，因为我们想要小根堆
};
priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> q(cmp);

void Astar(){
    q.push({n,0});
    while(!q.empty()){
        int u=q.top().first;
        int d=q.top().second;
        q.pop();
        //注意 这里不能有vis判断 因为即使在队列中  也可以再次进入队列
        if(u==1){
            ans[++tot]=d;
            if(tot==k){
                return ;
            }
        }
        for(int i=head[u];i;i=Next[i]){
            int v=to[i];
            int w=weight[i];
            q.push({v,w+d});
        }
    }
}

int main()
{
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addedge(u,v,w);
        Addedge(v,u,w);
    }
    dijkstra();
    Astar();
    for(int i=1;i<=tot;i++){
        cout<<ans[i]<<endl;
    }
    for(int i=tot+1;i<=k;i++){
        cout<<"-1"<<endl;
    }
    return 0;
}
