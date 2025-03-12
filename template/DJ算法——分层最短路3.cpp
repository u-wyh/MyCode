#include<bits/stdc++.h>
using namespace std;
const int MAXN = 10005;
const int MAXM = 100005;
const int MAXK = 11;

struct Range {
    int cur,t,cost;
};
// �ȽϺ���������С���ѣ��� l ֵ���ʱ������ͨ����Ӷ���ıȽ��������ȶ���
bool compare(const Range& a, const Range& b) {
    return a.cost > b.cost; // ע�������Ǵ��ںţ���Ϊ����Ҫʹ�� greater<> �����С����
}
priority_queue<Range, vector<Range>, decltype(&compare)> heap(compare);
int n,m,k,st,en;
int head[MAXN];
int Next[MAXM];
int weight[MAXM];
int to[MAXM];
int cnt=1;
int dis[MAXN][MAXK];
bool visited[MAXN][MAXK];

int main()
{
    cin>>n>>m>>k>>st>>en;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        Next[cnt]=head[u];
        to[cnt]=v;
        weight[cnt]=w;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        weight[cnt]=w;
        head[v]=cnt++;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<=k;j++){
            dis[i][j]=INT_MAX;
            visited[i][j]=false;
        }
    }
    dis[st][0]=0;
    heap.push({st,0,0});
    while (!heap.empty()) {
        Range record = heap.top();
        heap.pop();
        int cur = record.cur;
        int t = record.t;
        int cost = record.cost;
        if (visited[cur][t]) {
            continue;
        }
        visited[cur][t] = true;
        if (cur == en) {
            // ������֦
            // �����յ�ֱ�ӷ���
            // ���õȶ�����
            cout<<cost;
            return 0;
        }
        for(int i=head[cur];i>0;i=Next[i]){
            int v=to[i];
            int w=weight[i];
            if(t<k&&dis[v][t+1]>dis[cur][t]){
                dis[v][t+1]=dis[cur][t];
                heap.push({v,t+1,cost});
            }
            if(dis[v][t]>dis[cur][t]+w){
                dis[v][t]=dis[cur][t]+w;
                heap.push({v,t,cost+w});
            }
        }
    }
    cout<<-1;
    return 0;
}
