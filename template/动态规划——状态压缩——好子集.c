#include<stdio.h>
#define MAXV  30
#define LIMIT  (1 << 10)
#define MOD  1000000007

int dp[MAXV + 1][LIMIT];
static int own[31] = {
    0b0000000000, // 0
    0b0000000000, // 1
    0b0000000001, // 2
    0b0000000010, // 3
    0b0000000000, // 4
    0b0000000100, // 5
    0b0000000011, // 6
    0b0000001000, // 7
    0b0000000000, // 8
    0b0000000000, // 9
    0b0000000101, // 10
    0b0000010000, // 11
    0b0000000000, // 12
    0b0000100000, // 13
    0b0000001001, // 14
    0b0000000110, // 15
    0b0000000000, // 16
    0b0001000000, // 17
    0b0000000000, // 18
    0b0010000000, // 19
    0b0000000000, // 20
    0b0000001010, // 21
    0b0000010001, // 22
    0b0100000000, // 23
    0b0000000000, // 24
    0b0000000000, // 25
    0b0000100001, // 26
    0b0000000000, // 27
    0b0000000000, // 28
    0b1000000000, // 29
    0b0000000111 // 30
};


// 1....i范围的数字，每种数字cnt[i]个
// 最终相乘的结果一定要让质因子的状态为s，且每种质因子只能有1个
// 请问子集的数量是多少
// s每一位代表的质因子如下
// 质数: 29 23 19 17 13 11 7 5 3 2
// 位置: 9 8 7 6 5 4 3 2 1 0
int f1(int i, int s, int* cnt) {
    if (dp[i][s] != -1) {
        return dp[i][s];
    }
    int ans = 0;
    if (i == 1) {
        if (s == 0) {
            ans = 1;
            for (int j = 0; j < cnt[1]; j++) {
                ans = (ans *2) % MOD;
            }
        }
    } else {
        ans = f1(i - 1, s, cnt);
        int cur = own[i];
        int times = cnt[i];
        if (cur != 0 && times != 0 && (s & cur) == cur) {
            // 能要i这个数字
				ans = (int) (((long) f1(i - 1, s ^ cur, cnt) * times + ans) % MOD);
			}
		}
    dp[i][s] = ans;
    return ans;
}

// 记忆化搜索
int numberOfGoodSubsets1(int* nums,int n) {
    // 1 ~ 30
    int cnt [MAXV + 1];
    for(int i=0;i<n;i++)
    {
        cnt[nums[i]]=0;
    }
    for(int i=0;i<n;i++)
    {
        cnt[nums[i]]++;
    }
    for (int i = 0; i<= MAXV; i++) {
        for(int j=0;j<=LIMIT;j++){
            dp[i][j]=-1;
        }
    }

    int ans = 0;
    for (int s = 1; s < LIMIT; s++) {
        ans = (ans + f1(MAXV, s, cnt)) % MOD;
    }
    return ans;
}

int main()
{
    int i=0;
    int nums[LIMIT];
    while(scanf("%d",&nums[i++])==1);
    int n=i-1;
    printf("%d\n",numberOfGoodSubsets1( nums,n));
    return 0;
}
