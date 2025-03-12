// 不含连续1的非负整数
// 给定一个正整数n，请你统计在[0, n]范围的非负整数中
// 有多少个整数的二进制表示中不存在连续的1
// 测试链接 : https://leetcode.cn/problems/non-negative-integers-without-consecutive-ones/
#include<bits/stdc++.h>
using namespace std;

int n;
int cnt[31];

// cnt[len] : 二进制如果有len位，所有二进制状态中不存在连续的1的状态有多少个，辅助数组
// 从num二进制形式的高位开始，当前来到第i位，之前的位完全和num一样
// 返回<=num且不存在连续的1的状态有多少个
int f(int num, int i) {
    if (i == -1) {
        return 1; // num自身合法
    }
    int ans = 0;
    if ((num & (1 << i)) != 0) {
        ans += cnt[i];
        if ((num & (1 << (i + 1))) != 0) {
            // 如果num二进制状态，前一位是1，当前位也是1
            // 如果前缀保持和num一样，后续一定不合法了
            // 所以提前返回
            return ans;
        }
    }
    // 之前的高位和num一样，且合法，继续去i-1位递归
    ans += f(num, i - 1);
    return ans;
}

int main()
{
    cin>>n;
    cnt[0] = 1;
    cnt[1] = 2;
    for (int len = 2; len <= 30; len++) {
        cnt[len] = cnt[len - 1] + cnt[len - 2];
    }
    cout<<f(n, 30);
    return 0;
}
