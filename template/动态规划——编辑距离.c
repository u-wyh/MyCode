/*
    这段代码是为了解决一个问题：将s1变为s2消耗最小的方法
    其中不同操作的代价分别是：插入 a    删除 b    替换 c
    dp[i][j]的含义是将s1的前i个字符换成s2的前j个字符所需要的最小代价
    如果s1 s2的实际有效字符长度分别是m n
    那么定义 int  dp[m+1][n+1]  我们所求的答案是dp[m][n]

    动态规划常用的后缀解决法
    在这道题中，我们可以以s1的第i个是否与s2的第j个一样来判断
    首先  如果s1的第i个需要参与比较
        1.如果s1的第i个要变成s2的第j个
            并且如果一样，说明完全不需要变，即dp[i][j]=dp[i-1][j-1]
            如果不一样，还要参与比较，那么只能替换 即dp[i][j]=c+dp[i-1][j-1]
        2.如果s1的第i个不要变成s2的第j个，还参与了比较
            在这样的情况下，只有说明s1的前i个要变成s2的前j-1个，然后插入一个就好，
            即dp[i][j]=dp[i][j-1]+a
    如果s1的第i个不需要参与比较
        那么只要删除就好，所以有dp[i][j]=dp[i-1][j]+b
    情况123都只能出现一个值，然后选择最小的成为dp[i][j]
*/

#include<stdio.h>
#include<string.h>
#define max 10000
//定义一个数组的最大长度，只是为了更好的输入数据而已，没有其他作用

int min(int a,int b)
{
    return a>b?b:a;
}

int f1(char *s1,char *s2,int a,int b,int c,int m,int n)
{
    int dp[m][n];
    for (int i = 0; i < m; i++) {
        dp[i][0] = i * b;
    }
    for (int j = 1; j < n; j++) {
        dp[0][j] = j * a;
    }
    for(int i=1;i<m;i++)
    {
        for(int j=1;j<n;j++)
        {
            int p1=10000000;
            int p2=10000000;
            //p1 p2 应该是最大的int型数值，在这里10000000足够了，而且p1 p2一定要赋初值
            //否则p1 p2不一定有值，会造成问题
            if(s1[i-1]==s2[j-1])
                p1=dp[i-1][j-1];
            if(s1[i-1]!=s2[j-1])
                p2=dp[i-1][j-1]+c;
            int p3=dp[i][j-1]+a;
            int p4=dp[i-1][j]+b;
            dp[i][j]=min(min(p1,p2),min(p3,p4));
        }
    }
    return dp[m-1][n-1];
}

int main()
{
    char s1[max],s2[max];
    int m,n;
    fgets(s1,max,stdin);
    fgets(s2,max,stdin);
    m=strlen(s1);
    n=strlen(s2);
    //这里要注意m n 还包含了一个终止符，它们已经是有效长度加1了
    int a,b,c;
    printf("please enter a b and c: ");
    scanf("%d %d %d",&a,&b,&c);
    printf("%5d\n",f1(s1,s2,a,b,c,m,n));
    return 0;
}
/*
    代码的优化：
        其实我们可以发现dp[i][j] 只与dp[i-1][j]  dp[i][j-1]  dp[i-1][j-1]有关（abc属于客观条件）
        如果我们把dp做成一张表，那么dp[i][j]只与上面的  左边的  左上的有关
        那我们把第一行   第一列填好后就可以依次填好第二行（列）  第三行（列）直到结束
        根据这个思路，我们可以压缩这个表，从而实现优化
*/
