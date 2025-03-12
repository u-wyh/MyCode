//P2149
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1500;
const int MAXM = MAXN*MAXN;

int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;

int head1[MAXN];
int Next1[MAXM];
int to1[MAXM];
int weight1[MAXM];
int in[MAXN];
int cnt1=1;

int len[MAXN];

int dis[5][MAXN];
bool vis[MAXN];
int st1,en1,st2,en2;
int n,m;

auto compare = [](const pair<int, int>& left, const pair<int, int>& right) {
    return left.second > right.second; // 注意这里是大于，因为我们想要小根堆
};
priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> heap(compare);

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

void addedge(int u,int v,int w){
    Next[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void addedge1(int u,int v,int w){
    Next1[cnt1]=head1[u];
    to1[cnt1]=v;
    weight1[cnt1]=w;
    head1[u]=cnt1++;
    in[v]++;
}

void dijkstra(int op,int st){
    for(int i=1;i<=n;i++){
        dis[op][i]=1e9;
        vis[i]=false;
    }
    dis[op][st]=0;
    heap.push({st,0});
    while(!heap.empty()){
        int u=heap.top().first;
        heap.pop();
        if(vis[u]){
            continue;
        }
        vis[u]=true;
        for(int i=head[u];i;i=Next[i]){
            int v=to[i];
            int w=weight[i];
            if(!vis[v]&&(w+dis[op][u])<dis[op][v]){
                dis[op][v]=dis[op][u]+w;
                heap.push({v,dis[op][v]});
            }
        }
    }
}

queue<int>q;

void topo(){
    for(int i=1;i<=n;i++){
        if(in[i]==0){
            q.push(i);
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head1[u];i;i=Next1[i]){
            int v=to1[i];
            in[v]--;
            len[v]=max(len[v],len[u]+weight1[i]);
            if(in[v]==0){
                q.push(v);
            }
        }
    }
}

int main()
{
    n=read(),m=read();
    st1=read(),en1=read(),st2=read(),en2=read();
    for(int i=1;i<=m;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedge(u,v,w);
        addedge(v,u,w);
    }
    dijkstra(1,st1);
    dijkstra(2,en1);
    dijkstra(3,st2);
    dijkstra(4,en2);
    for(int i=1;i<=n;i++){
        for(int j=head[i];j;j=Next[j]){
            int v=to[j];
            if(dis[1][i]+weight[j]+dis[2][v]==dis[1][en1]){
                if(dis[3][i]+weight[j]+dis[4][v]==dis[3][en2]){
                    addedge1(i,v,weight[j]);
                }
            }
        }
    }
    topo();
    int ans=0;
    for(int i=1;i<=n;i++){
        ans=max(ans,len[i]);
    }
    for(int i=1;i<=n;i++){
        len[i]=0;
        in[i]=0;
        head1[i]=0;
    }
    cnt1=1;
    for(int i=1;i<=n;i++){
        for(int j=head[i];j;j=Next[j]){
            int v=to[j];
            if(dis[1][i]+weight[j]+dis[2][v]==dis[1][en1]){
                if(dis[4][i]+weight[j]+dis[3][v]==dis[3][en2]){
                    addedge1(i,v,weight[j]);
                }
            }
        }
    }
    topo();
    for(int i=1;i<=n;i++){
        ans=max(ans,len[i]);
    }
    cout<<ans<<endl;
    return 0;
}
