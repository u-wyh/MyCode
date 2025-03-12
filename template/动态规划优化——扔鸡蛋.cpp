// 大楼扔鸡蛋问题
// 一共有k枚相同的鸡蛋，一共有n层楼
// 已知一定存在楼层f(0<=f<=n)，从>f的楼层扔鸡蛋一定会碎，从<=f的楼层扔鸡蛋，扔几次都不会碎
// 鸡蛋一旦碎了就不能再使用，只能选择另外的鸡蛋
// 现在想确定f的值，返回最少扔几次鸡蛋，可以确保测出该值
// 1 <= k <= 100
// 1 <= n <= 10^4
// 测试链接 : https://leetcode.cn/problems/super-egg-drop/
#include<bits/stdc++.h>
using namespace std;

int n,k;
int dp[10005][105];

int main()
{
    cin>>n>>k;
    if(k==1){
        cout<<n;
    }
    else{
        for (int j = 1; j <= n; j++) {
			for (int i = 1; i <= k; i++) {
				dp[i][j] = dp[i - 1][j - 1] + dp[i][j - 1] + 1;
				if (dp[i][j] >= n) {
					cout<<j;
					return 0;
				}
			}
		}
    }
    return 0;
}
