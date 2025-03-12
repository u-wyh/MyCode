/*
    这段代码是用于记录字符串s中有多少个子串和t一样
    我们代码的方法是判断是s的前i个字符中有多少个t的前j个字符
    于是有了dp[i][j]
    我们所求的是dp[m][n]其中m n分别是s t的有效长度

*/
#include<stdio.h>
#include<string.h>
#define maxest 100

int f1(char* s, char *t,int m,int n) {
    int dp[m][n];
    for(int j=1;j<n;j++)
        dp[0][j]=0;
    for(int i=0;i<m;i++)
        dp[i][0]=1;
    for (int i = 1; i <m; i++) {
        for (int j = 1; j <n; j++) {
            dp[i][j] = dp[i - 1][j];
            if (s[i - 1] == t[j - 1]) {
                dp[i][j] += dp[i - 1][j - 1];
            }
        }
    }
    return dp[m-1][n-1];
}
int main()
{
    char s[maxest],t[maxest];
    fgets(s,maxest,stdin);
    fgets(t,maxest,stdin);
    int m=strlen(s);
    int n=strlen(t);
    printf("%5d %5d\n",m,n);
    int dp[m][n];
    //我们所得到的m n是有效长度的加上1  包含一个'\0'
    for(int j=0;j<n;j++)
        dp[0][j]=0;
    for(int i=0;i<m;i++)
        dp[i][0]=1;
    printf("%5d\n",f1(s,t,m,n));
    return 0;
}
