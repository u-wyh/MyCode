// ����Ϊk����ȵ��Ӽ�
// ����һ����������  nums ��һ�������� k��
// �ҳ��Ƿ��п��ܰ��������ֳ� k ���ǿ��Ӽ������ܺͶ���ȡ�
// �������� : https://leetcode.cn/problems/partition-to-k-equal-sum-subsets/
#include<bits/stdc++.h>
using namespace std;

int n,k;
int sum=0,limit;
int nums[20];

// limit : ÿ���߹涨�ĳ���
// status : ��ʾ��Щ���ֻ�����ѡ
// cur : ��ǰҪ������������Ѿ��γɵĳ���
// rest : һ�����м�����û�н��
// ���� : �ܷ��ù����л��ȥ���ʣ�µ����б�
// ��Ϊ�����ӹ���֮ǰ��һ����֤ÿ�����ۼ�������������limit
// ����status�Ǿ���cur��rest�ģ��ؼ��ɱ����ֻ��status
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
