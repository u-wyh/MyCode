#include<bits/stdc++.h>
using namespace std;
const int MAXM = 250000;
const int MAXN = 500;

int n,m;
vector<vector<int >>graph;
//使用邻接表建图
int edge[MAXM][2];
//输入的边数据
int quiet[MAXN];
//输入的安静数值
int indegree[MAXN];
//各个节点的入度
int ans[MAXN];
//每个节点的答案
queue<int>q;

int main()
{
    cin>>n>>m;
    graph.resize(n);//初始化动态数组大小
    for(int i=1;i<=m;i++){
        cin>>edge[i][0]>>edge[i][1];
    }
    for(int i=0;i<n;i++){
        cin>>quiet[i];
    }
    for(int i=1;i<=m;i++){
        graph[edge[i][0]].push_back(edge[i][1]);
        //建图
        indegree[edge[i][1]]++;
        //增加入度
    }
    for(int i=0;i<n;i++){
        if(indegree[i]==0){
            q.push(i);
        }
    }
    for(int i=0;i<n;i++){
        ans[i]=i;
        //首先将每个节点答案初始化为本身
    }
    while(!q.empty()){
        int cur=q.front();
        q.pop();
        for(int i=0;i<graph[cur].size();i++){
            if(quiet[ans[graph[cur][i]]]>quiet[ans[cur]]){
                ans[graph[cur][i]]=ans[cur];
            }
            //将这个即将出去的节点所有功能结算
            indegree[graph[cur][i]]--;
            if(indegree[graph[cur][i]]==0){
                q.push(graph[cur][i]);
            }
        }
    }
    for(int i=0;i<n;i++){
        printf("%3d",ans[i]);
    }
    return 0;
}
