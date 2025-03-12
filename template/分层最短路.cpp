//P3831
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

int n,m;
struct point{
    int x,y,id;
}nums[MAXN];
int st,en;

int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;

int dis[MAXN<<1];
bool vis[MAXN<<1];
auto compare = [](const pair<int, int>& left, const pair<int, int>& right) {
    return left.second > right.second; // 注意这里是大于，因为我们想要小根堆
};
priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> heap(compare);

void addedge(int u,int v,int w){
    Next[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

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

bool cmp(point x,point y){
    return x.x==y.x?x.y>y.y:x.x<y.x;
}

bool cmp1(point x,point y){
    return x.y==y.y?x.x>y.x:x.y<y.y;
}

void dijkstra(){
    for(int i=1;i<=2*n+5;i++){
        dis[i]=INT_MAX;
    }
    dis[st]=0;
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
            if(!vis[v]&&w+dis[u]<dis[v]){
                dis[v]=w+dis[u];
                heap.push({v,dis[v]});
            }
        }
    }
}

int main()
{
    n=read(),m=read();
    n=m+2;
    st=n-1,en=n;
    for(int i=1;i<=n;i++){
        nums[i].x=read(),nums[i].y=read();
        nums[i].id=i;
    }
    for(int i=1;i<=n-2;i++){
        addedge(i,i+n,1);
        addedge(i+n,i,1);
    }
    addedge(st,st+n,0);
    addedge(st+n,st,0);
    addedge(en,en+n,0);
    addedge(en+n,en,0);
    sort(nums+1,nums+n+1,cmp);
    for(int i=1;i<n;i++){
        if(nums[i].x==nums[i+1].x){
            addedge(nums[i].id,nums[i+1].id,(nums[i].y-nums[i+1].y)*2);
            addedge(nums[i+1].id,nums[i].id,(nums[i].y-nums[i+1].y)*2);
        }
    }
    sort(nums+1,nums+n+1,cmp1);
    for(int i=1;i<n;i++){
        if(nums[i].y==nums[i+1].y){
            addedge(nums[i].id+n,nums[i+1].id+n,(nums[i].x-nums[i+1].x)*2);
            addedge(nums[i+1].id+n,nums[i].id+n,(nums[i].x-nums[i+1].x)*2);
        }
    }
    dijkstra();
    if(dis[en]==INT_MAX){
        cout<<-1<<endl;
        return 0;
    }
    cout<<dis[en];
    return 0;
}
