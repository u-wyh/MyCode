// 最优账单平衡
// 给你一个表示交易的数组 transactions
// 其中 transactions[i] = [fromi, toi, amounti]
// 表示 ID = fromi 的人给 ID = toi 的人共计 amounti
// 请你计算并返回还清所有债务的最小交易笔数
// 测试链接 : https://leetcode.cn/problems/optimal-account-balancing/

#include<bits/stdc++.h>
using namespace std;

int n;
int tran[100][3];
int help[100];
int debt[100];
int cnt=0;

int f(int status, int sum, int* dp) {
    if (dp[status] != -1) {
        return dp[status];
    }
    int ans = 0;
    if ((status & (status - 1)) != 0) { // 集合中不只一个元素
        if (sum == 0) {
            for (int i = 0; i < n; i++) {
                if ((status & (1 << i)) != 0) {
                    // 找到任何一个元素，去除这个元素
                    // 剩下的集合进行尝试，返回值 + 1
                    ans = f( status ^ (1 << i), sum - debt[i], dp) + 1;
                    // 然后不需要再尝试下一个元素了，因为答案一定是一样的
                    // 所以直接break
                    break;
                }
            }
        } else {
            for (int i = 0; i < n; i++) {
                if ((status & (1 << i)) != 0) {
                    ans = max(ans, f( status ^ (1 << i), sum - debt[i], dp));
                }
            }
        }
    }
    dp[status] = ans;
    return ans;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>tran[i][0]>>tran[i][1]>>tran[i][2];
    }
    for(int i=1;i<=n;i++){
        help[tran[i][0]]+=tran[i][2];
        help[tran[i][1]]-=tran[i][2];
    }
    for (int num : help) {
        if (num != 0) {
            cnt++;
        }
    }
    int index = 0;
    for (int num : help) {
        if (num != 0) {
            debt[index++] = num;
        }
    }
    n=index;
    int dp[1 << n];
    memset(dp, -1, sizeof(dp));
    cout<< n - f((1 << n) - 1, 0, dp);
    return 0;
}
