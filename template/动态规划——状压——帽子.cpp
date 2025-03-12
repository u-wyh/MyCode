// ÿ���˴���ͬñ�ӵķ�����
// �ܹ��� n ���˺� 40 �ֲ�ͬ��ñ�ӣ�ñ�ӱ�Ŵ� 1 �� 40
// ����һ�������б���б� hats ������ hats[i] �ǵ� i ��������ϲ��ñ�ӵ��б�
// �����ÿ���˰���һ����ϲ����ñ�ӣ�ȷ��ÿ���˴���ñ�Ӹ����˶���һ���������ط�����
// ���ڴ𰸿��ܴܺ󣬴𰸶� 1000000007 ȡģ
// �������� : https://leetcode.cn/problems/number-of-ways-to-wear-different-hats-to-each-other
#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;

int n,m;
int dp[41][1<<11];

// m : ñ����ɫ�����ֵ, 1 ~ m
// n : �˵�������0 ~ n-1
// i : ������ʲô��ɫ��ñ��
// s : n���ˣ�˭û����״̬����0��˭������״̬����1
// dp : ���仯�����ı�
// ���� : �ж����ַ���
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
    // 1 ~ m ñ�ӣ���������Щ�ˣ�״̬��Ϣ -> int
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
