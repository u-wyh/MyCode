#include<stdio.h>
#include<string.h>
#define Max 501

int min(int a,int b)
{
    return a<b?a:b;
}

int f1(char *str,int l,int r)
{
    if(l==r)
        return 0;
    if(l+1==r)
        return str[l]==str[r]?0:1;
    if(str[l]==str[r])
        return f1(str,l+1,r-1);
    else
        return min(f1(str,l,r-1),f1(str,l+1,r))+1;
}

int f2(char *str,int n)
{
    int dp[n][n];
    for(int i=0;i<n;i++)
    {
        dp[i][i]=0;
        dp[i][i+1]=(str[i]==str[i+1]?0:1);
    }

    for (int l = n - 3; l >= 0; l--) {
        for (int r = l + 2; r < n; r++) {
            if (str[l] == str[r]) {
                dp[l][r] = dp[l + 1][r - 1];
            } else {
                dp[l][r] = min(dp[l][r - 1], dp[l + 1][r]) + 1;
            }
        }
    }
    return dp[0][n-1];
}
/*
注意这道题得出dp所需要的数据是左边  下边  和左下边的数据
所以我们只能从dp表的下边开始填充数据  沿对角线开始填
*/
int main()
{
    char str[Max];
    fgets(str,Max,stdin);
    int n=strlen(str)-1;
    //n是字符串有效字符数
    printf("%5d\n",f1(str,0,n-1));
    printf("%5d\n",f2(str,n));
    return 0;
}
