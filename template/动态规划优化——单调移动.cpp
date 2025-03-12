// 最小移动总距离
// 所有工厂和机器人都分布在x轴上
// 给定长度为n的二维数组factory，factory[i][0]为i号工厂的位置，factory[i][1]为容量
// 给定长度为m的一维数组robot，robot[j]为第j个机器人的位置
// 每个工厂所在的位置都不同，每个机器人所在的位置都不同，机器人到工厂的距离为位置差的绝对值
// 所有机器人都是坏的，但是机器人可以去往任何工厂进行修理，但是不能超过某个工厂的容量
// 测试数据保证所有机器人都可以被维修，返回所有机器人移动的最小总距离
// 1 <= n、m <= 100
// -10^9 <= factory[i][0]、robot[j] <= +10^9
// 0 <= factory[i][1] <= m
// 测试链接 : https://leetcode.cn/problems/minimum-total-distance-traveled/
#include<bits/stdc++.h>
using namespace std;
const long NA = LONG_MAX;
const int MAXN = 101;
const int MAXM = 101;

int n, m;
// 工厂下标从1开始，fac[i][0]表示位置，fac[i][1]表示容量
struct node{
    int pos,cap;
}fac[MAXN];
// 机器人下标从1开始，rob[i]表示位置
int rob[MAXM];
// dp[i][j] : 1...i工厂去修理1...j号机器人，最短总距离是多少
long dp[MAXN][MAXM];
// 前缀和数组
long sum[MAXM];
// 单调队列
int q[MAXM];
int l, r;

bool cmp(node a,node b){
    return a.pos<b.pos;
}

// i号工厂和j号机器人的距离
long dist(int i, int j) {
    return abs((long) fac[i].pos - rob[j]);
}

// i号工厂从j号机器人开始负责的指标
// 真的可行，返回指标的值
// 如果不可行，返回NA
long value(int i, int j) {
    if (dp[i - 1][j - 1] == NA) {
        return NA;
    }
    return dp[i - 1][j - 1] - sum[j - 1];
}

void build() {
    // 工厂和机器人都根据所在位置排序
    sort(fac+1,fac+n+1,cmp);
    sort(rob+1,rob+m+1);
    // dp初始化
    for (int j = 1; j <= m; j++) {
        dp[0][j] = NA;
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>fac[i].pos>>fac[i].cap;
    }
    for(int i=1;i<=m;i++){
        cin>>rob[i];
    }
    build();
    for (int i = 1, cap; i <= n; i++) {
        // i号工厂的容量
        cap = fac[i].cap;
        // sum[j]表示
        // 1号机器人去往i号工厂的距离
        // 2号机器人去往i号工厂的距离
        // ...
        // j号机器人去往i号工厂的距离
        // 上面全加起来，也就是前缀和的概念
        for (int j = 1; j <= m; j++) {
            sum[j] = sum[j - 1] + dist(i, j);
        }
        l = r = 0;
        for (int j = 1; j <= m; j++) {
            dp[i][j] = dp[i - 1][j];
            if (value(i, j) != NA) {
                while (l < r && value(i, q[r - 1]) >= value(i, j)) {
                    r--;
                }
                q[r++] = j;
            }
            if (l < r && q[l] == j - cap) {
                l++;
            }
            if (l < r) {
                dp[i][j] = min(dp[i][j], value(i, q[l]) + sum[j]);
            }
        }
    }
    cout<<dp[n][m];
    return 0;
}
