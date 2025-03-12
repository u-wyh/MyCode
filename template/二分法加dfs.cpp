//P5021
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;

int n,m;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;
int need;
int tag[MAXN<<1];
int que[MAXN<<1];
int tail;
int dp[MAXN];

void addedge(int u,int v,int w){
    Next[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void dfs(int u,int f,int limit){
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            dfs(v,u,limit);
        }
    }
    tail=0;
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            que[++tail]=dp[v]+weight[i];
        }
    }
    sort(que+1,que+tail+1);
    for(int i=tail;i>=1&&que[i]>=limit;i--){
        need--,tail--;
    }
    for(int i=1;i<=tail;i++){
        if(tag[i]!=u){
            int l=i+1,r=tail,nxt=tail+1;
            while(l<=r){
                int mid=(l+r)/2;
                if(que[mid]>=limit-que[i]){
                    nxt=mid;
                    r=mid-1;
                }
                else{
                    l=mid+1;
                }
            }
            while(tag[nxt]==u&&nxt<=tail){
                nxt++;
            }
            if(nxt<=tail){
                tag[nxt]=u;
                tag[i]=u;
                need--;
            }
        }
    }
    dp[u]=0;
    for(int i=tail;i>=1;i--){
        if(tag[i]!=u){
            dp[u]=que[i];
            break;
        }
    }
}

bool check(int limit){
    need=m;
    dfs(1,0,limit);
    if(need<=0)
        return true;
    else
        return false;
}

int main()
{
    cin>>n>>m;
    int l=0,r,ans=0;
    for(int i=1,u,v,w;i<n;i++){
        cin>>u>>v>>w;
        addedge(u,v,w);
        addedge(v,u,w);
        r+=w;
    }
    while(l<=r){
        int mid=(l+r)/2;
        if(check(mid)){
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
        memset(tag,0,sizeof(tag));
    }
    cout<<ans<<endl;
    return 0;
}
