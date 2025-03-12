#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100;

int n,m;
vector<vector<int >>graph;
int indegree[MAXN];
int edge[MAXN][2];
queue<int>Q;

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>edge[i][0]>>edge[i][1];
    }
    graph.resize(n);
    for(int i=1;i<=m;i++){
        graph[edge[i][1]].push_back(edge[i][0]);
        indegree[edge[i][0]]++;
    }
    for(int i=0;i<n;i++){
        if(indegree[i]==0){
            Q.push(i);
        }
    }
    while(!Q.empty()){
        int cur=Q.front();
        Q.pop();
        printf("%3d",cur);
        for(int i=0;i<graph[cur].size();i++){
            indegree[graph[cur][i]]--;
            if(indegree[graph[cur][i]]==0){
                Q.push(graph[cur][i]);
            }
        }
    }
    return 0;
}
