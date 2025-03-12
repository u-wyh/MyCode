#include<bits/stdc++.h>
using namespace std;
const int MAXN = 11;
const int MAXM = 21;

int t;

//邻接矩阵以及邻接表变量
int n,m;
int nums[MAXN][MAXN];
int edge[MAXM][3];
vector<vector<pair<int ,int>>>graph;

//链式前向星变量
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;

void build(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            nums[i][j]=0;
        }
    }
    //邻接矩阵的清空

    graph.resize(n+1);
    graph.clear();
    //邻接表的清空

    cnt=1;
    memset(head,0,sizeof(head));
    //链式前向星只需要清空head就可以  其他的数据还会被覆盖
}

void directgraph(){
    //邻接矩阵建图
    for(int i=1;i<=m;i++){
        nums[edge[i][0]][edge[i][1]]=edge[i][2];
    }

    //邻接表建图
    for(int i=1;i<=m;i++){
        graph[edge[i][0]].push_back({edge[i][1],edge[i][2]});
    }

    //链式前向星建图
    for(int i=1;i<=m;i++){
        Next[cnt]=head[edge[i][0]];
        to[cnt]=edge[i][1];
        weight[cnt]=edge[i][2];
        head[edge[i][0]]=cnt++;
    }
}

void showgraph(){
    cout<<endl;
    //邻接矩阵
    cout<<"邻接矩阵遍历： \n";
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            printf("%3d",nums[i][j]);
        }
        printf("\n");
    }
    cout<<endl;

    //邻接表
    cout<<"邻接表遍历：\n";
    for(int i=1;i<=n;i++){
        cout<<i<<"(邻居，边权): ";
        for(int j=0;j<graph[i].size();j++){
            cout<<"("<<graph[i][j].first<<" ,"<<graph[i][j].second<<" )";
        }
        cout<<endl;
    }
    cout<<endl;

    //链式前向星
    cout<<"链式前向星输出：\n";
    for(int i=1;i<=n;i++){
        cout<<i<<"(邻居，边权): ";
        for(int j=head[i];j>0;j=Next[j]){
            cout<<"("<<to[j]<<" ,"<<weight[j]<<" )";
        }
        cout<<endl;
    }
    cout<<endl;
}

int main()
{
    cin>>t;
        while(t--){
        cin>>n>>m;
        for(int i=1;i<=m;i++){
            cin>>edge[i][0]>>edge[i][1]>>edge[i][2];
        }
        //有向带权图
        build();
        directgraph();
        showgraph();
        system("pause");
    }
    return 0;
}
