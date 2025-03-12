// 信封问题(错排问题)
// 一共n个人，每个人都写了一封信
// 每个人必须寄出一封信，每个人必须收到一封信，并且不能自己寄给自己
// 返回一共有多少种寄信的方法
// 1 <= n <= 20
// 测试链接 : https://www.luogu.com.cn/problem/P1595
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include<bits/stdc++.h>
using namespace std;

// 普通动态规划的方法
long ways1(int n) {
    long dp[n + 1];
    for (int i = 1; i <= n; i++) {
        if (i == 1) {
            dp[i] = 0;
        } else if (i == 2) {
            dp[i] = 1;
        } else {
            dp[i] = (i - 1) * (dp[i - 1] + dp[i - 2]);
        }
    }
    return dp[n];
}

// 二项式反演的方法
long ways2(int n) {
    long facn = 1; // n!
    for (int i = 1; i <= n; i++) {
        facn *= i;
    }
    long ans = facn; // i = 0时的项
    long faci = 1; // i!
    for (int i = 1; i <= n; i++) {
        // i = 1...n
        // (-1)的i次方 * (n! / i!)
        faci = faci * i;
        if ((i & 1) == 0) {
            ans += facn / faci;
        } else {
            ans -= facn / faci;
        }
    }
    return ans;
}

int main()
{
    int n;
    cin>>n;
    //cout<<ways1(n)<<endl;
    cout<<ways2(n)<<endl;
    return 0;
}
