/*
最低票价
在一个火车旅行很受欢迎的国度，你提前一年计划了一些火车旅行
在接下来的一年里，你要旅行的日子将以一个名为 days 的数组给出
每一项是一个从 1 到 365 的整数
火车票有 三种不同的销售方式
一张 为期1天 的通行证售价为 costs[0] 美元
一张 为期7天 的通行证售价为 costs[1] 美元
一张 为期30天 的通行证售价为 costs[2] 美元
通行证允许数天无限制的旅行
例如，如果我们在第 2 天获得一张 为期 7 天 的通行证
那么我们可以连着旅行 7 天(第2~8天)
返回 你想要完成在给定的列表 days 中列出的每一天的旅行所需要的最低消费
测试链接 : https://leetcode.cn/problems/minimum-cost-for-tickets/
*/

#include<stdio.h>
#include<limits.h>
#define max 365

static int durations[3]={1,7,30};
//旅游套餐时长方案0 1 2分别是1 7 30

int f1(int* days, int* price, int i,int n) {
    if (i == n) {
        // 后续已经无旅行了
        return 0;
    }
    // i下标 : 第days[i]天，有一场旅行
    // i.... 最少花费是多少
    int ans = INT_MAX;
    for (int k = 0, j = i; k < 3; k++) {
        // k是方案编号 : 0 1 2
        while (j < n && days[i] + durations[k] > days[j]) {
            // 因为方案2持续的天数最多，30天
            // 所以while循环最多执行30次
            // 枚举行为可以认为是O(1)
            // 设置条件是  j不超过n
            // 循环中的 days[i] + durations[k] > days[j]   在选择当前的第k种方案的情况下  可以实现第几个旅行目标
            j++;
        }
        ans = ans> (price[k] + f1(days, price, j,n))?(price[k] + f1(days, price, j,n)):ans;
    }
    return ans;
}
//以上是暴力算法计算最低票价


int mincostTickets2(int* days, int* price,int n) {
    int dp[n];
    for (int i = 0; i < n; i++) {
        dp[i] = INT_MAX;
    }
    return f2(days,price, 0,n, dp);
}

int f2(int* days, int* price, int i, int n,int* dp) {
    if (i == n) {
        return 0;
    }
    if (dp[i] != INT_MAX) {
        return dp[i];
    }
    int ans = INT_MAX;
    for (int k = 0, j = i; k < 3; k++) {
        while (j < n && days[i] + durations[k] > days[j]) {
            j++;
        }
        ans = ans> (price[k] + f2(days, price, j,n,dp))?(price[k] + f2(days, price, j,n,dp)):ans;
    }
    dp[i] = ans;
    return ans;
}
//使用储存的方法来减少时间

int main()
{
    int days[max];
    int i=0;
    while(scanf("%d",&days[i++])==1);
    //days[i] 表示第i天要旅行
    int n=--i;
    //表示一共有n天是需要旅行的

    int price[3];//定义方案0 1 2的三种票价
    for(i=0;i<3;i++)
    {
        scanf("%d",&price[i]);
    }
    printf("\n");

    printf("%d\n",f1(days,price,0,n));
    printf("%d\n",mincostTickets2(days,price,n));
    return 0;
}
