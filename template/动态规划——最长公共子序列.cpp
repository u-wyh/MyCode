//题目链接：P1439
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
char s1[MAXN];
char s2[MAXN];
int dp[1000][1000];

int f1(int m,int n)
{
    if(m<0||n<0)
        return 0;
    int p1=f1(m-1,n-1);
    int p2=f1(m,n-1);
    int p3=f1(m-1,n);
    int p4=s1[m]==s2[n]?(p1+1):0;
    return max(max(p1,p2),max(p3,p4));
}
//暴力递归版本

int f2(int m,int n)
{
    if(m<0||n<0)
        return 0;
    int ans;
    if (s1[m - 1] == s2[n - 1]) {
        ans = f2(m - 1, n - 1) + 1;
    } else {
        ans = max(f2(m - 1, n), f2(m, n - 1));
    }
    return ans;
}
//版本一的等效写法

int f3(int len1, int len2) {
    if (len1 == 0 || len2 == 0) {
        return 0;
    }
    if (dp [len1][len2] != -1) {
        return dp[len1][len2];
    }
    int ans;
    if (s1[len1 - 1] == s2[len2 - 1]) {
        ans = f3(len1 - 1, len2 - 1) + 1;
    } else {
        ans = max(f3(len1 - 1, len2), f3( len1, len2 - 1));
    }
    dp[len1][len2] = ans;
    return ans;
}

int longest() {
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = -1;
        }
    }
    return f3(n,n);
}
//记忆化搜索版本

int longest2() {
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            if(i==0||j==0)
                dp[i][j]=0;
        }
    }
    for (int len1 = 1; len1 <= n; len1++) {
        for (int len2 = 1; len2 <= n; len2++) {
            if (s1[len1 - 1] == s2[len2 - 1]) {
                dp[len1][len2] = 1 + dp[len1 - 1][len2 - 1];
            }
            else {
                dp[len1][len2] = max(dp[len1 - 1][len2], dp[len1][len2 - 1]);
            }
        }
    }
    return dp[n][n];
}

int main()
{
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>s1[i];
    }
    for(int i=0;i<n;i++){
        cin>>s2[i];
    }
    cout<<f1(n-1,n-1)<<endl;
    cout<<f2(n-1,n-1)<<endl;
    cout<<longest()<<endl;
    cout<<longest2()<<endl;
    return 0;
}
