#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5005;
const int MAXM = 500005;
const int MOD = 80112002;

int n,m,cnt=1;
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int edge[MAXM][2];
int indegree[MAXN];
int line[MAXN];
int ans=0;
queue<int >pq;

signed main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>edge[i][0]>>edge[i][1];
    }
    for(int i=1;i<=m;i++){
        Next[cnt]=head[edge[i][0]];
        to[cnt]=edge[i][1];
        head[edge[i][0]]=cnt++;
        indegree[edge[i][1]]++;
    }
    for(int i=1;i<=n;i++){
        if(indegree[i]==0){
            pq.push(i);
            line[i]=1;
        }
        //printf("%3d %3d %3d\n",indegree[i],line[i],head[i]);
    }
    while(!pq.empty()){
        int cur=pq.front();
        pq.pop();
        if(head[cur]==0){
            ans=(ans+line[cur])%MOD;
        }else{
            for(int i=head[cur];i>0;i=Next[i]){
                indegree[to[i]]--;
                line[to[i]]=(line[cur]+line[to[i]])%MOD;
                if(indegree[to[i]]==0){
                    pq.push(to[i]);
                }
            }
        }
    }
    cout<<ans;
    return 0;
}
