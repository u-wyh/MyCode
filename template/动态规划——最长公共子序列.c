/*
 最长公共子序列
 给定两个字符串text1和text2
 返回这两个字符串的最长 公共子序列 的长度
 如果不存在公共子序列，返回0
 两个字符串的 公共子序列 是这两个字符串所共同拥有的子序列
 测试链接 : https://leetcode.cn/problems/longest-common-subsequence/
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 1000

int max(int a,int b)
{
    return a>b?a:b;
}

int f1(char *s1,char *s2,int m,int n)
{
    if(m<0||n<0)
        return 0;
    int p1=f1(s1,s2,m-1,n-1);
    int p2=f1(s1,s2,m,n-1);
    int p3=f1(s1,s2,m-1,n);
    int p4=s1[m]==s2[n]?(p1+1):0;
    return max(max(p1,p2),max(p3,p4));
}

int f2(char *s1,char *s2,int m,int n)
{
    if(m==0||n==0)
        return 0;
    int ans;
    if (s1[m - 1] == s2[n - 1]) {
        ans = f2(s1, s2, m - 1, n - 1) + 1;
    } else {
        ans = max(f2(s1, s2, m - 1, n), f2(s1, s2, m, n - 1));
    }
    return ans;
}

int f3(char* s1, char* s2, int len1, int len2, int dp[len1+1][len2+1]) {
    if (len1 == 0 || len2 == 0) {
        return 0;
    }
    if (dp [len1][len2] != -1) {
        return dp[len1][len2];
    }
    int ans;
    if (s1[len1 - 1] == s2[len2 - 1]) {
        ans = f3(s1, s2, len1 - 1, len2 - 1, dp) + 1;
    } else {
        ans = max(f3(s1, s2, len1 - 1, len2, dp), f3(s1, s2, len1, len2 - 1, dp));
    }
    dp[len1][len2] = ans;
    return ans;
}

int longest(char *s1,char *s2 ,int m,int n) {
    int dp [m + 1][n + 1];
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = -1;
        }
    }
    return f3(s1, s2, m ,n , dp);
}

int longest2(char *s1,char *s2 ,int m,int n) {
    int dp [m + 1][n + 1];
    for(int i=0;i<=m;i++)
    {
        for(int j=0;j<=n;j++)
        {
            if(i==0||j==0)
                dp[i][j]=0;
        }
    }
    for (int len1 = 1; len1 <= m; len1++) {
        for (int len2 = 1; len2 <= n; len2++) {
            if (s1[len1 - 1] == s2[len2 - 1]) {
                dp[len1][len2] = 1 + dp[len1 - 1][len2 - 1];
            }
            else {
                dp[len1][len2] = max(dp[len1 - 1][len2], dp[len1][len2 - 1]);
            }
        }
    }
    return dp[m][n];
}

int main()
{
    char s1[MAX];
    char s2[MAX];
    fgets(s1, MAX, stdin);
    fgets(s2, MAX, stdin);
    int  len1 = strlen(s1);
    if (len1 > 0 && s1[len1-1] == '\n') {
        s1[len1-1] = '\0';
    }
    int len2 = strlen(s2);
    if (len2 > 0 && s2[len2-1] == '\n') {
        s2[len2-1] = '\0';
    }
//注意len1 len2 中都含有一个\0   占了一个数字
    printf("%5d\n",longest2(s1,s2,len1-1,len2-1));
    printf("%5d\n",longest(s1,s2,len1-1,len2-1));
    printf("%5d\n",f1(s1,s2,len1-1,len2-1));
    printf("%5d\n",f2(s1,s2,len1-1,len2-1));
    return 0;
}
