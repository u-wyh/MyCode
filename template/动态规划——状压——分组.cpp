// 划分为k个相等的子集
// 给定一个整数数组  nums 和一个正整数 k，
// 找出是否有可能把这个数组分成 k 个非空子集，其总和都相等。
// 测试链接 : https://leetcode.cn/problems/partition-to-k-equal-sum-subsets/
#include<bits/stdc++.h>
using namespace std;

int n,k;
int sum=0,limit;
int nums[20];

// limit : 每条边规定的长度
// status : 表示哪些数字还可以选
// cur : 当前要解决的这条边已经形成的长度
// rest : 一共还有几条边没有解决
// 返回 : 能否用光所有火柴去解决剩下的所有边
// 因为调用子过程之前，一定保证每条边累加起来都不超过limit
// 所以status是决定cur和rest的，关键可变参数只有status
bool f(int status, int cur, int rest, int* dp){
    if(rest==0){
        return true;
    }
    if(dp[status]!=0){
        return dp[status]==1;
    }
    bool ans=false;
    for(int i=0;i<n;i++){
        if(status&(1<<i)&&cur+nums[i]<=limit){
            if(cur+nums[i]==limit){
                ans=f(status^(1<<i),0,rest-1,dp);
            }
            else{
                ans=f(status^(1<<i),cur+nums[i],rest,dp);
            }
            if(ans)
                break;
        }
    }
    dp[status]=ans?1:-1;
    return ans;
}

bool subsets(){
    if(sum%k!=0)
        return false;
    limit=sum/k;
    int dp[1<<n];
    for(int i=0;i<(1<<n);i++)
        dp[i]=0;
    return f((1 << n) - 1, 0, k, dp);
}

int main()
{
    cin>>n>>k;
    for(int i=0;i<n;i++){
        cin>>nums[i];
        sum+=nums[i];
    }
    if(subsets()){
        cout<<"yes";
    }
    else{
        cout<<"no";
    }
    return 0;
}
