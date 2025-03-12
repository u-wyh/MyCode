// 摘樱桃
// 给定一个n*n的正方形矩阵grid，每个格子值只有三种-1、0、1
// -1表示格子不能走、0表示格子可以走但是没有樱桃、1表示格子可以走且有一颗樱桃
// 你的目标是从左上角走到右下角，每一步只能 向下 或者 向右
// 然后从右下角走回左上角，每一步只能 向上 或者 向左
// 这个过程中，想尽量多的获得樱桃，但是有樱桃的格子，只能捡一次
// 返回最多能获得多少樱桃，如果不存在通路返回0
// 测试链接 : https://leetcode.cn/problems/cherry-pickup/
// 这里只讲述核心思路
// 有兴趣同学自己改出严格位置依赖的动态规划
// 有兴趣同学自己改出空间压缩版本的动态规划
// 之前的课大量涉及，这里不再赘述
#include<iostream>
#include<cmath>
using namespace std;

int n;
int grid[50][50];
int dp[50][50][50];

int f(int a,int b,int c){
    int d=a+b-c;
    if(grid[a][b]==-1||grid[c][d]==-1||a==n||b==n||c==n||d==n){
        return -1;
    }
    if(a==n-1&&b==n-1){
        return grid[a][b];
    }
    if (dp[a][b][c] != -2) {
        return dp[a][b][c];
    }
    int get = a == c && b == d ? grid[a][b] : (grid[a][b] + grid[c][d]);
    int next = f(a + 1, b, c + 1);
    next = max(next, f(a + 1, b, c));
    next = max(next, f(a, b + 1, c + 1));
    next = max(next, f(a, b + 1, c));
    int ans = -1;
    if (next != -1) {
        ans = get + next;
    }
    dp[a][b][c] = ans;
    return ans;
}

int main()
{
    cin>>n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>grid[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                dp[i][j][k] = -2;
            }
        }
    }
    int ans = f(0, 0, 0);
    ans=ans == -1 ? 0 : ans;
    cout<<ans;
    return 0;
}
