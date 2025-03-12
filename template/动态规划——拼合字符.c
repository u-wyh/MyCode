#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#define max 1000

bool isInterleave1(char *s1,char *s2,char *s3,int m,int n,int k) {
    if ((m+n)!=k) {
        return false;
    }
    bool dp [m + 1][n + 1];
    for(int i=0;i<=m;i++)
    {
        for(int j=0;j<=n;j++)
        {
            if(i==0||j==0)
                dp[i][j]=false;
        }
    }
    dp[0][0] = true;
    for (int i = 1; i <= m; i++) {
        if (s1[i - 1] != s3[i - 1]) {
            break;
        }
        dp[i][0] = true;
    }
    for (int j = 1; j <= n; j++) {
        if (s2[j - 1] != s3[j - 1]) {
            break;
        }
        dp[0][j] = true;
    }
    //完成数组的初始化
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] = (s1[i - 1] == s3[i + j - 1] && dp[i - 1][j]) || (s2[j - 1] == s3[i + j - 1] && dp[i][j - 1]);
        }
    }
    return dp[n][m];
}

int main()
{
    char s1[max],s2[max],s3[max];
    int m,n,k;
    fgets(s1,max,stdin);
    fgets(s2,max,stdin);
    fgets(s3,max,stdin);
    m=strlen(s1)-1;
    n=strlen(s2)-1;
    k=strlen(s3)-1;
    //此时m n k 是三个字符串的有效长度
    if(isInterleave1(s1,s2,s3,m,n,k)==true)
        printf("YES\n");
    else
        printf("NO\n");
    return 0;
}
