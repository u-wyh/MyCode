#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100001;
const int MAXM = 100001;

int head[MAXN];
int Next[MAXM];
int to[MAXM];
int edge[MAXM][2];
int indegree[MAXN];
int cnt=1;
int n,m;
priority_queue<int, vector<int>, greater<int>> pq;

int main()
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
        }
    }
    while(!pq.empty()){
        int cur=pq.top();
        pq.pop();
        printf("%d ",cur);
        for(int i=head[cur];i!=0;i=Next[i]){
            indegree[to[i]]--;
            if(indegree[to[i]]==0){
                pq.push(to[i]);
            }
        }
    }
    return 0;
}
