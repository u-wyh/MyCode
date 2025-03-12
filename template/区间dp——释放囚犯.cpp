//P1622
#include<bits/stdc++.h>
using namespace std;

int a[105];
int dp[105][105];
int n,m;

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>a[i];
    }
    a[0]=0,a[m+1]=n+1;
    for(int len=1;len<=m;len++){
        for(int i=1;i+len-1<=m;i++){
            int j=i+len-1;
            dp[i][j]=1e9;
            for(int k=i;k<=j;k++){
                //枚举最先释放的囚犯  此时i-1 j+1位置上的囚犯已经释放
                dp[i][j]=min(dp[i][j],dp[i][k-1]+dp[k+1][j]+a[j+1]-a[i-1]-1-1);
            }
        }
    }
    cout<<dp[1][m]<<endl;
    return 0;
}
