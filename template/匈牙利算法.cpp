#include<bits/stdc++.h>
using namespace std;

int n,m;            //M, N分别表示左、右侧集合的元素数量
int graph[20][20]; //邻接矩阵存图
int p[20];         //记录当前右侧元素所对应的左侧元素
bool vis[20];      //记录右侧元素是否已被访问过

bool match(int i){
    for (int j = 1; j <= m; j++){
        if (graph[i][j] && !vis[j]) {
            //有边且未访问
            vis[j] = true;                 //记录状态为访问过
            if (p[j] == 0 || match(p[j])) {
                //如果暂无匹配，或者原来匹配的左侧元素可以找到新的匹配
                p[j] = i;    //当前左侧元素成为当前右侧元素的新匹配
                return true; //返回匹配成功
            }
        }
    }
    return false; //循环结束，仍未找到匹配，返回匹配失败
}

int Hungarian(){
    int cnt = 0;
    for (int i = 1; i <= n; i++){
        memset(vis, 0, sizeof(vis)); //重置vis数组
        if (match(i))
            cnt++;
        for(int i=1;i<=n;i++){
            cout<<p[i]<<' ';
        }
        cout<<endl;
    }
    return cnt;
}

int main()
{
    cin>>n>>m;
    int k;
    cin>>k;
    for(int i=1;i<=k;i++){
        int u,v;
        cin>>u>>v;
        graph[u][v]=true;
    }
    cout<<Hungarian()<<endl;
    for(int i=1;i<=n;i++){
        cout<<p[i]<<' ';
    }
    cout<<endl;
    return 0;
}

/*
数据
4 4
6
1 2 1 4 2 2 3 1 3 3 4 4


ans:3
*/
