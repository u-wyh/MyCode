#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int v[m],p[m],q[m],cost[m],val[m],king[m],fans[m],follows[m][2];
    for(int i=0;i<m;i++)
    {
        fans[i]=0;
        scanf("%d %d %d",&v[i],&p[i],&q[i]);
        cost[i]=v[i];
        //代表购买这个所需要的代价
        val[i]=v[i]*p[i];
        //代表这个物品的价值
        if(q[i]==0)
            king[i]=1;
        else
            king[i]=0;
        //判断这个物件是主件还是附件
    }
    for(int i=0;i<m;i++)
    {
        if(king[i]==0)
            follows[q[i]-1][fans[q[i]-1]++]=i+1;
        /*
            如果king[i]==0，那么第i件物品是附件
            q[i]-1  对应的是它的主件
            fans[]  的值只能是0 1 2
            follows[q[i]-1][fans[q[i]-1]++]=i+1的含义是
            这个附件所属的主件的所拥有的附件数量增加1
            follows的第二个只能是0 1
        */
    }
    int dp[m+1][n+1];
    for(int i=0;i<=n;i++)
        dp[0][i]=0;
    //dp[i][j]的含义是在前i个物品中不超过代价j最大的价值
    int k = 0;
    //k是上一次更新的数据
    for (int i = 1, fan1, fan2; i <= m; i++) {
        if (king[i-1]) {
            for (int j = 0; j <= n; j++) {
                // dp[i][j] : 0...i范围上，只关心主商品，并且进行展开
                //            花费不超过j的情况下，获得的最大收益
                // 可能性1 : 不考虑当前主商品
                dp[i][j] = dp[k][j];
                if (j - cost[i-1] >= 0) {
                    // 可能性2 : 考虑当前主商品，只要主
                    dp[i][j] = max(dp[i][j], dp[k][j - cost[i-1]] + val[i-1]);
                }
                // fan1 : 如果有附1商品，编号给fan1，如果没有，fan1 == -1
                // fan2 : 如果有附2商品，编号给fan2，如果没有，fan2 == -1
                fan1 = fans[i-1] >= 1 ? follows[i-1][0] : -1;
                fan2 = fans[i-1] >= 2 ? follows[i-1][1] : -1;
                if (fan1 != -1 && j - cost[i-1] - cost[fan1-1] >= 0) {
                    // 可能性3 : 主 + 附1
                    dp[i][j] = max(dp[i][j], dp[k][j - cost[i-1] - cost[fan1-1]] + val[i-1] + val[fan1-1]);
                }
                if (fan2 != -1 && j - cost[i-1] - cost[fan2-1] >= 0) {
                    // 可能性4 : 主 + 附2
                    dp[i][j] = max(dp[i][j], dp[k][j - cost[i-1] - cost[fan2-1]] + val[i-1] + val[fan2-1]);
                }
                if (fan1 != -1 && fan2 != -1 && j - cost[i-1] - cost[fan1-1] - cost[fan2-1] >= 0) {
                    // 可能性5 : 主 + 附1 + 附2
                    dp[i][j] = max(dp[i][j], dp[k][j - cost[i-1] - cost[fan1-1] - cost[fan2-1]]
                                    + val[i-1] + val[fan1-1] + val[fan2-1]);
                }
            }
        k = i;
        }
    }
    printf("%d\n",dp[m][n]);
    return 0;
}
