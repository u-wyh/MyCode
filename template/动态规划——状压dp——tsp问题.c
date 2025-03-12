#include<stdio.h>
#include<limits.h>

int dp[1<<20][20];
int graph[20][20];

int min(int a,int b)
{
    return a<b?a:b;
}

int f(int s,int i,int n)
{
    if (s == (1 << n) - 1) {
        // n : 000011111
        return graph[i][0];
    }
    if (dp[s][i] != -1) {
        return dp[s][i];
    }
    int ans = INT_MAX;
    for (int j = 0; j < n; j++) {
        // 0...n-1这些村，都看看是不是下一个落脚点
        if ((s & (1 << j)) == 0) {
            ans = min(ans, graph[i][j] + f(s | (1 << j), j,n));
        }
    }
    dp[s][i] = ans;
    return ans;
}

int main()
{
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            scanf("%d",&graph[i][j]);
        }
    }
    for (int s = 0; s < (1 << n); s++) {
        for (int i = 0; i < n; i++) {
            dp[s][i] = -1;
        }
    }
    printf("%d\n",f(1,0,n));
    return 0;
}
