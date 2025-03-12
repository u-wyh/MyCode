#include<stdio.h>
#include<stdbool.h>
#define Max 1000

// limit : 每条边规定的长度
// status : 表示哪些数字还可以选
// cur : 当前要解决的这条边已经形成的长度
// rest : 一共还有几条边没有解决
// 返回 : 能否用光所有火柴去解决剩下的所有边
// 因为调用子过程之前，一定保证每条边累加起来都不超过limit
// 所以status是决定cur和rest的，关键可变参数只有status
bool f(int* nums, int limit, int status, int cur, int rest, int* dp,int n)
{
    if (rest == 0) {
        return status == 0;
    }
    if (dp[status] != 0) {
        return dp[status] == 1;
    }
    bool ans = false;
    for (int i = 0; i < n; i++) {
        // 考察每一根火柴，只能使用状态为1的火柴
    if ((status & (1 << i)) != 0 && cur + nums[i] <= limit) {
				if (cur + nums[i] == limit) {
                ans = f(nums, limit, status ^ (1 << i), 0, rest - 1, dp,n);
            } else {
                ans = f(nums, limit, status ^ (1 << i), cur + nums[i], rest, dp,n);
            }
            if (ans) {
                break;
            }
        }
    }
    dp[status] = ans ? 1 : -1;
    return ans;
}

bool makesquare(int *nums,int sum,int n)
{
    if (sum % 4 != 0) {
        return false;
    }
    int dp [1 << n];
    for(int i=0;i<(1<<n);i++)
        dp[i]=0;
    return f(nums, sum / 4, (1 << n) - 1, 0, 4, dp,n);
}

int main()
{
    int i=0;
    int nums[Max];
    while(scanf("%d",&nums[i++])==1);
    int n=i-1;
    int sum=0;
    for(int i=0;i<n;i++)
        sum+=nums[i];
    if(makesquare(nums,sum, n))
        printf("yes\n");
    else
        printf("no\n");
    return 0;
}
