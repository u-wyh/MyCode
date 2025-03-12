/*
这段代码的作用是建造一个二叉树结构，一共有n个节点，高度不得超过m，一共有多少种方式  对mod取余
dp[i][j]的含义是建造一个二叉树结构，一共有i个节点，高度不得超过j，一共有多少种方式  对mod取余
我们所需要的答案是dp[n][m]  所以我们设置int dp[n+1][m+1]
我们每一个都要有头结点，然后分为左边 右边各自多少个节点
以此类推，得到答案
*/
#include<stdio.h>
#define MOD 1000000007

static int dp[100][100];
//这里我们本来应该设置为dp[n+1][m+1]，但是为了方便，dp[100][100]就可以了

int compute(int n,int m)
{
    long ans=0;
    if(n==0)
        return 1;
    if(m==0)
        return 0;
    if(dp[n][m]!=-1)
        return (int)dp[n][m];
    for (int k = 0; k < n; k++) {
        ans = (ans + ((long) compute(k, m - 1) * compute(n - k - 1, m - 1)) % MOD) % MOD;
    }
    dp[n][m] = ans;
    return (int) ans;
}

int main()
{
    int n,m;
    printf("please enter the n and m: ");
    scanf("%d %d",&n,&m);
    //int dp[n+1][m+1];
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
        {
            dp[i][j]=-1;
        }
    }
    printf("%5d\n",compute(n,m));
    return 0;
}
