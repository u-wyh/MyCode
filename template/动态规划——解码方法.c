/*
这段代码的意思是将一串数字字符转换为英语字符有多少种办法
那么至多存在两种情况，第一种是一个数字代表一个字符，第二种是和下一个数字共同组成一个字符
*/
#include<stdio.h>
#include<string.h>
#define max 10000

int f1(char *s,int i,int n)
{
    if(i==n)
        return 1;
    int ans;
    if(s[i]=='0')
        ans=0;
    else
    {
        ans=f1(s,i+1,n);
        if(i+1<=n&&((s[i]-'0')*10+(s[i+1]-'0'))<=26)
            ans+=f1(s,i+2,n);
    }
    return ans;
}
//暴力算法计算


int kinds(char *s,int n)
{
    int dp[n];
    for(int i=0;i<n;i++)
    {
        dp[i]=-1;
    }
    return f2(s,0,n,dp);
}

int f2(char *s,int i,int n,int *dp)
{
    if(i==n)
        return 1;
    if(dp[i]!=-1)
        return dp[i];
    int ans;
    if(s[i]=='0')
        ans=0;
    else
    {
        ans=f1(s,i+1,n);
        if(i+1<=n&&((s[i]-'0')*10+(s[i+1]-'0'))<=26)
            ans+=f1(s,i+2,n);
    }
    dp[i]=ans;
    return ans;
}


int kinds2(char *s,int n) {
    int dp[n + 1];
    dp[n] = 1;
    //解释一下为什么全部初始化1 因为dp还没有建立联系  就是只有一个长度的字符   所以为1
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == '0') {
            dp[i] = 0;
        } else {
            dp[i] = dp[i + 1];
            if (i + 1 <n && ((s[i] - '0') * 10 + s[i + 1] - '0') <= 26) {
                dp[i] += dp[i + 2];
            }
        }
    }
    return dp[0];
}
//dp[i]的含义是以下标i开头的字符串可以形成多少种解码方法
//滚动规划，先算出 i+1  i+2然后推出i

int main()
{
    char s[max];
    gets(s);
    int n=strlen(s);
    printf("%d\n",n);
    printf("%d\n",f1(s,0,n));
    printf("%d\n",kinds(s,n));
    printf("%d\n",kinds2(s,n));
    return 0;
}
