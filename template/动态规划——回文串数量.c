#include<stdio.h>
#include<string.h>
#define mod 1000000007
#define Max 100

static long long dp[Max][Max];

int main()
{
    char s[Max];
    fgets(s,Max,stdin);
    int n=strlen(s)-1;
    int last [256];
    // left[i] : i位置的左边和s[i]字符相等且最近的位置在哪，不存在就是-1
    int left [n];
    for(int i=0;i<256;i++)
        last[i]=-1;
    for (int i = 0; i < n; i++) {
        left[i] = last[s[i]];
        last[s[i]] = i;
    }
    // right[i] : i位置的右边和s[i]字符相等且最近的位置在哪，不存在就是n
    int right [n];
    for(int i=0;i<n;i++)
        last[i]=n;
    for (int i = n - 1; i >= 0; i--) {
        right[i] = last[s[i]];
        last[s[i]] = i;
    }
    for (int i = 0; i < n; i++) {
        dp[i][i] = 1;
    }
    for (int i = n - 2, l, r; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            if (s[i] != s[j]) {
                // a ..... b
                // i       j
                dp[i][j] = dp[i][j - 1] + dp[i + 1][j] - dp[i + 1][j - 1] + mod;
            }
            else
            {
                // s[i] == s[j]
                // a......a
                // i      j
                l = right[i];
                r = left[j];
                if (l > r) {
                    // i...j的内部没有s[i]字符
                    // a....a
                    // i    j
                    // (i+1..j-1) + a(i+1..j-1)a + a + aa
                    dp[i][j] = dp[i + 1][j - 1] * 2 + 2;
                } else if (l == r) {
                    // i...j的内部有一个s[i]字符
                    // a.....a......a
                    // i     lr     j
                    // (i+1..j-1) + a(i+1..j-1)a + aa
                    dp[i][j] = dp[i + 1][j - 1] * 2 + 1;
                } else {
                    // i...j的内部不只一个s[i]字符
                    // a...a....这内部可能还有a但是不重要....a...a
                    // i   l                             r   j
                    dp[i][j] = dp[i + 1][j - 1] * 2 - dp[l + 1][r - 1] + mod;
					}
                }
            dp[i][j] %= mod;
        }
    }
    printf("%lld\n",dp[0][n-1]);
    return 0;
}
