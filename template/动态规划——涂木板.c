/*
这段代码的含义是：对于一定长度的字符，给出他的最终形态，我们每次可以将连续的几个字符变换为几个相同的字符
                  请问最小的代价是什么（一开始字符串是空的）
    dp[i][j]的含义是从下标i到下标j的字符要想变为最终形态，需要最小的代价是什么
    如果只有一个字符  那么一次就好了
    如果只有两个字符  并且他们相等  一次就好
                              不相等  需要两次
    否则，从最左边的进行分割，使之成为两个部分  求最小值
*/
#include<stdio.h>
#include<string.h>
#include<limits.h>

#define Max 51

static int dp[Max][Max];

int min(int a,int b)
{
    return a<b?a:b;
}

int compute(char *s,int n)
{
    for(int i=0;i<n-1;i++)
    {
        dp[i][i]=1;
        dp[i][i+1]= s[i]==s[i+1] ? 1 : 2;
    }
    dp[n-1][n-1]=1;
    for(int l=n-3,ans;l>=0;l--)
    {
        for(int r=l+2;r<n;r++)
        {
            if(s[l]==s[r])
                dp[l][r]=dp[l][r-1];
            else
            {
                ans=INT_MAX;
                for(int m=l;m<r;m++)
                    ans=min(ans,dp[l][m]+dp[m+1][r]);
                dp[l][r]=ans;
            }
        }
    }
    return dp[0][n-1];
}

int main()
{
    char s[Max];
    fgets(s,Max,stdin);
    int n=strlen(s)-1;
    printf("%d\n",compute(s,n));
    return 0;
}
