#include<stdio.h>
#include<string.h>
#define max 10000

int main()
{
    char str[max];

    int i=0;
    while((str[i++]=getchar())!='\n');
    int n=i-1;
    int s[n];
    for(int i=0;i<n;i++)
    {
        s[i]=str[i]-'a';
    }
    int dp [26];
    for(int i=0;i<26;i++)
        dp[i]=0;
    dp[s[0]] = 1;
    int ans=0;
    for (int i = 1, cur, pre, len = 1; i < n; i++) {
        cur = s[i];
        pre = s[i - 1];
        // pre cur
        if ((pre + 1)%26 == cur) {
            len++;
        } else {
            len = 1;
        }
        dp[cur] = dp[cur]>len?dp[cur]:len;
    }
    for (int i = 0; i < 26; i++) {
        ans += dp[i];
    }
    printf("%d\n",ans);
    return 0;
}
