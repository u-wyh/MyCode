// 每个人戴不同帽子的方案数
// 总共有 n 个人和 40 种不同的帽子，帽子编号从 1 到 40
// 给你一个整数列表的列表 hats ，其中 hats[i] 是第 i 个人所有喜欢帽子的列表
// 请你给每个人安排一顶他喜欢的帽子，确保每个人戴的帽子跟别人都不一样，并返回方案数
// 由于答案可能很大，答案对 1000000007 取模
// 测试链接 : https://leetcode.cn/problems/number-of-ways-to-wear-different-hats-to-each-other
#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;

int n,m;
int dp[41][1<<11];

// m : 帽子颜色的最大值, 1 ~ m
// n : 人的数量，0 ~ n-1
// i : 来到了什么颜色的帽子
// s : n个人，谁没满足状态就是0，谁满足了状态就是1
// dp : 记忆化搜索的表
// 返回 : 有多少种方法
int f1(int* hats,int i, int status) {
    if(status==(1<<n)-1){
        return 1;
    }
    if(i==(m+1))
        return 0;
    if(dp[i][status]!=-1)
        return dp[i][status];
    int ans=f1(hats,i+1,status);
    int now=hats[i];
    for(int p=0;p<n;p++){
        if ((status & (1 << p)) == 0 && (now & (1 << p)) != 0) {
            ans = (ans + f1(hats, i + 1, status | (1 << p))) % MOD;
        }
    }
    dp[i][status]=ans;
    return ans;
}

int main()
{
    cin>>n;
    vector<int>vec[n];
    for(int i=0,k;i<n;i++){
        cin>>k;
        for(int j=0;j<k;j++){
            int num;
            cin>>num;
            vec[i].push_back(num);
            m=max(num,m);
        }
    }
    // 1 ~ m 帽子，能满足哪些人，状态信息 -> int
    int hats[41];
    for(int i=0;i<=m;i++){
        hats[i]=0;
    }
    for (int pi = 0; pi < n; pi++) {
        for (int j=0;j<vec[pi].size();j++) {
            int hat=vec[pi][j];
            hats[hat] |= 1 << pi;
        }
    }
//    for(int i=0;i<=m;i++){
//        cout<<hats[i]<<' ';
//    }
    memset(dp,-1,sizeof(dp));
    cout<<f1(hats,1,0);
    return 0;
}
