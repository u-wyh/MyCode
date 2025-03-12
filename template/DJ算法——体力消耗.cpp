// 最小体力消耗路径
// 你准备参加一场远足活动。给你一个二维 rows x columns 的地图 heights
// 其中 heights[row][col] 表示格子 (row, col) 的高度
// 一开始你在最左上角的格子 (0, 0) ，且你希望去最右下角的格子 (rows-1, columns-1)
// （注意下标从 0 开始编号）。你每次可以往 上，下，左，右 四个方向之一移动
// 你想要找到耗费 体力 最小的一条路径
// 一条路径耗费的体力值是路径上，相邻格子之间高度差绝对值的最大值
// 请你返回从左上角走到右下角的最小 体力消耗值
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const int MAXM = 105;

struct Range {
    int i,j,val;
};
// 比较函数，用于小根堆，当 l 值相等时，可以通过添加额外的比较来保持稳定性
bool compare(const Range& a, const Range& b) {
    return a.val > b.val; // 注意这里是大于号，因为我们要使用 greater<> 来获得小根堆
}
priority_queue<Range, vector<Range>, decltype(&compare)> heap(compare);
int walk[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
int n,m;
int height[MAXN][MAXM];
//记录各个地方的海拔
int dis[MAXN][MAXM];
//记录从开始到达目前这个点最小的最大高度差
bool visit[MAXN][MAXM];
//记录这个点是否被访问

int main()
{
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>height[i][j];
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            dis[i][j]=INT_MAX;
        }
    }
    //初始化

    dis[0][0]=0;
    heap.push({0,0,0});
    while(!heap.empty()){
        Range u=heap.top();
        heap.pop();
        int x=u.i;
        int y=u.j;
        int c=u.val;
        if(visit[x][y]){
            continue;
        }
        visit[x][y]=true;
        if(x==n-1&&y==m-1){
            cout<<c;
            return 0;
        }
        //如果到达目标直接弹出
        for (int i = 0; i < 4; i++) {
            int nx = x + walk[i][0];
            int ny = y + walk[i][1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visit[nx][ny]) {
                int nc = max(c,abs(height[x][y] - height[nx][ny]));
                if (nc < dis[nx][ny]) {
                    dis[nx][ny] = nc;
                    heap.push( { nx, ny, nc });
                }
            }
        }
    }
    return 0;
}
