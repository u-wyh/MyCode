// 统计整数数目
// 给你两个数字字符串 num1 和 num2 ，以及两个整数max_sum和min_sum
// 如果一个整数 x 满足以下条件，我们称它是一个好整数
// num1 <= x <= num2
// min_sum <= digit_sum(x) <= max_sum
// 请你返回好整数的数目
// 答案可能很大请返回答案对10^9 + 7 取余后的结果
// 注意，digit_sum(x)表示x各位数字之和
// 测试链接 : https://leetcode.cn/problems/count-of-integers/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MOD 1000000007
#define MAXN 23
#define MAXM 401
#define Max  10000

int dp[MAXN][MAXM][2];
//dp[i][sum][free] 表示已经选择了前i位并且他们的和为sum   free表示状态是否可以随便选  的方案数
char *num;
int min, max, len;

void build() {
    for (int i = 0; i < len; i++) {
        for (int j = 0; j <= max; j++) {
            dp[i][j][0] = -1;
            dp[i][j][1] = -1;
        }
    }
}
//完成全局变量的初始化

int f(int i, int sum, int free) {
    if (sum > max)
        return 0;
    //表示现在的选择过大  已经不可能了  所以停止
    if (sum + (len - i) * 9 < min)
        return 0;
    //表示现在的选择过小  已经不可能了  所以停止
    if (i == len)
        return 1;
    //表示所有的数字已经填好   成功结束  返回1
    if (dp[i][sum][free] != -1)
        return dp[i][sum][free];

    int cur = num[i] - '0';
    int ans = 0;
    if (free == 0) {
        //选择有限制
        for (int pick = 0; pick < cur; pick++) {
            ans = (ans + f(i + 1, sum + pick, 1)) % MOD;
        }
        ans = (ans + f(i + 1, sum + cur, 0)) % MOD;
    } else {
        //选择没有限制
        for (int pick = 0; pick <= 9; pick++) {
            ans = (ans + f(i + 1, sum + pick, 1)) % MOD;
        }
    }
    dp[i][sum][free] = ans;
    return ans;
}

int count(char *num1, char *num2, int min_sum, int max_sum) {
    min = min_sum;
    max = max_sum;
    num = strdup(num2);
    len = strlen(num);
    build();
    int ans = f(0, 0, 0);
    //这是从0到大的数之间的答案

    free(num);
    num = strdup(num1);
    len = strlen(num);
    build();
    ans = (ans - f(0, 0, 0) + MOD) % MOD;
    //f(0,0,0)是从0到（小的数-1）之间的答案（较小的数需要特判）   需要减去
    //因为输入的是数字串 文本型  如果较小的数是1000000.....的话  a-1不好处理

    int sum = 0;
    for (int i = 0; i < len; i++) {
        sum += num[i] - '0';
    }
    if (sum >= min && sum <= max) {
        ans = (ans + 1) % MOD;
    }
    //特判小的那个数本身是否符合要求

    free(num);
    return ans;
}

int main() {
    char num1[Max];
    char num2[Max];
    scanf("%s",num1);
    scanf("%s",num2);
    int min_sum, max_sum;
    scanf("%d %d",&min_sum,&max_sum);
    printf("Result: %d\n", count(num1, num2, min_sum, max_sum));
    return 0;
}
