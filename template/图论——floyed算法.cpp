#include<bits/stdc++.h>
using namespace std;
const int MAXN = 101;
const int MAXM = 10001;

int n,m,ans;
int dis[MAXN][MAXN];
int path[MAXM];

void build() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dis[i][j] = INT_MAX;
        }
    }
}

void floyd() {
    // O(N^3)的过程
    // 枚举每个跳板
    // 注意，跳板要最先枚举！跳板要最先枚举！跳板要最先枚举！
    for (int bridge = 0; bridge < n; bridge++) { // 跳板
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // i -> .....bridge .... -> j
                // distance[i][j]能不能缩短
                // distance[i][j] = min ( distance[i][j] , distance[i][bridge] + distance[bridge][j])
                if (dis[i][bridge] != INT_MAX
                        && dis[bridge][j] != INT_MAX
                        && dis[i][j] > dis[i][bridge] + dis[bridge][j]) {
                    dis[i][j] = dis[i][bridge] + dis[bridge][j];
                }
            }
        }
    }
}

int main()
{
    cin>>n>>m;
    //build();
    //正常情况下，是需要我们自己建立邻接矩阵的
    for(int i=1;i<=m;i++){
        cin>>path[i];
        path[i]--;
        //注意下标的对应
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>dis[i][j];
            //这道题直接给出来邻接矩阵  不需要我们建立
        }
    }
    floyd();
    for(int i=1;i<m;i++){
        ans+=dis[path[i]][path[i+1]];
    }
    cout<<ans;
    return 0;
}
