/*
这段代码的作用是将一个只包含中括号和小括号的字符串，插入几个字符可以使整个字符串都对应
dp[l][r]的作用是从下标l到下标r最少插入几个字符可以使之完全对应
    如果只有一个字符，那么补充一个就可以让他们对应
    如果这样两个字符，那么他们对应，那么直接就是好的  0
                              不对应，那么就要插入两个才行   2
    否则，要划分为左右两边进行计算
*/
#include<stdio.h>
#include<string.h>
#include<limits.h>
#define Max 1000

static int dp[Max][Max];

int min(int a,int b)
{
    return a<b?a:b;
}

int f1(char *str,int l,int r)
{
    if(l==r)
        return 1;
    if(l==r-1)
    {
        if((str[l]=='('&&str[r]==')')||(str[l]=='['&&str[r]==']'))
            return 0;
        else
            return 2;
    }
    if(dp[l][r]!=-1)
        return dp[l][r];
    int p1=INT_MAX;
    if((str[l]=='('&&str[r]==')')||(str[l]=='['&&str[r]==']'))
        p1=f1(str,l+1,r-1);
    int p2=INT_MAX;
    for(int m=l;m<r;m++)
    {
        p2=min(p2,f1(str,l,m)+f1(str,m+1,r));
    }
    int ans=min(p1,p2);
    dp[l][r]=ans;
    return ans;
}

int compute(char *str,int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            dp[i][j]=-1;
        }
    }
    return f1(str,0,n-1);
}

int main()
{
    char str[Max];
    fgets(str,Max,stdin);
    int n=strlen(str)-1;
    //n是实际有效字符串长度
    printf("%d\n",compute(str,n));
    return 0;
}
