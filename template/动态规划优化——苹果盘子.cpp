// 数的划分方法
// 将整数m分成n份，且每份不能为空，任意两个方案不相同(不考虑顺序)
// 比如，m=7、n=3，那么(1, 1, 5) (1, 5, 1) (5, 1, 1)认为是同一种方法
// 返回有多少种不同的划分方法
// 测试链接 : https://www.luogu.com.cn/problem/P1025
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有用例
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 201;
const int MAXK = 7;

int dp[MAXN][MAXK];
int n,k;

int f(int n,int k){
    if(n==0){
        return 1;
    }
    if(k==0){
        return 0;
    }
    if(dp[n][k]!=-1){
        return dp[n][k];
    }
    int ans;
    if(k>n){
        //盘子比苹果多  那么注定了一定最多只会有n个盘子有东西
        ans=f(n,n);
    }
    else{
        ans=f(n,k-1)+f(n-k,k);//分别表示  不使用所有盘子  和  一定使用所有盘子（每个盘子至少有一个）
    }
    dp[n][k]=ans;
    return ans;
}

int main()
{
    cin>>n>>k;
    if(n<k)
        cout<<0<<endl;
    else if(n==k)
        cout<<1<<endl;
    else{
        n-=k;
        for(int i=0;i<=n;i++){
            for(int j=0;j<=k;j++){
                dp[i][j]=-1;
            }
        }
        cout<<f(n,k)<<endl;
    }
    return 0;
}
