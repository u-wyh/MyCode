//P1462
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e4+5;
const int MAXM = 1e5+5;

int n,m,b;
int cost[MAXN];
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;
long long blood[MAXN];
bool vis[MAXN];
auto compare = [](const pair<int, long long>& left, const pair<int, long long>& right) {
    return left.second > right.second; // 注意这里是大于，因为我们想要小根堆
};

priority_queue<pair<int, long long>, vector<pair<int, long long>>, decltype(compare)> heap(compare);

void addedge(int u,int v,int w){
    Next[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

bool check(int limit){
    for(int i=1;i<=n;i++){
        blood[i]=LLONG_MAX;
        vis[i]=false;
    }
    blood[1]=0;
    heap.push({1,0});
    while(!heap.empty()){
        int u=heap.top().first;
        heap.pop();
        if(vis[u]){
            continue;
        }
        vis[u]=true;
        for(int i=head[u];i>0;i=Next[i]){
            int v=to[i];
            int w=weight[i];
            if(cost[v]>limit){
                continue;
            }
            if(!vis[v]&&(w+blood[u])<blood[v]){
                blood[v]=w+blood[u];
                heap.push({v,blood[u]+w});
            }
        }
    }
    if(blood[n]>b){
        return false;
    }
    return true;
}

signed main()
{
    cin>>n>>m>>b;
    int l,r=0;
    for(int i=1;i<=n;i++){
        cin>>cost[i];
        r=max(cost[i],r);
    }
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addedge(u,v,w);
        addedge(v,u,w);
    }
    l=max(cost[1],cost[n]);
    int ans=0;
    while(l<=r){
        int mid=(l+r)/2;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    if(ans==0){
        cout<<"AFK"<<endl;
    }
    else{
        cout<<ans<<endl;
    }
    return 0;
}
