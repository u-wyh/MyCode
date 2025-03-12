// 不含连续1的非负整数
// 给定一个正整数n，请你统计在[0, n]范围的非负整数中
// 有多少个整数的二进制表示中不存在连续的1
// 测试链接 : https://leetcode.cn/problems/non-negative-integers-without-consecutive-ones/
#include<stdio.h>

// cnt[len] : 二进制如果有len位，所有二进制状态中不存在连续的1的状态有多少个，辅助数组
// 从num二进制形式的高位开始，当前来到第i位，之前的位完全和num一样
// 返回<=num且不存在连续的1的状态有多少个

//先打表  方便计算
//这个表是为了相同数位进行服务的
int f(int* cnt, int num, int i) {
    if (i == -1) {
        return 1; // num自身合法
    }
    int ans = 0;
    if ((num & (1 << i)) != 0) {
        //如果该位上的数字是1的话 我们可以选1和0  我们选择0  那么我们直接就可以加上cnt的值
        ans += cnt[i];//0 到 i-1     一共有i位  所以是cnt[i]
        //这个地方相当于是直接结算了   不用在考虑后面的位数了
        //只要原来的地方是1   我们将这个位置写0   直接结算
        if ((num & (1 << (i + 1))) != 0) {
            // 如果num二进制状态，前一位是1，当前位也是1
            // 如果前缀保持和num一样，后续一定不合法了
            // 所以提前返回
            //说明当前不能选1
            return ans;
        }
    }
    // 之前的高位和num一样，且合法，继续去i-1位递归
    ans += f(cnt, num, i - 1);
    //如果该位上的数字是0的话 我们只可以选0
    return ans;
}

int findIntegers1(int n) {
    int cnt[31];
    cnt[0] = 1;
    cnt[1] = 2;
    for (int len = 2; len <= 30; len++) {
        cnt[len] = cnt[len - 1] + cnt[len - 2];
    }
    return f(cnt, n, 30);
}

int findIntegersIterative(int n) {
    int cnt[31];
    cnt[0] = 1;
    cnt[1] = 2;
    for (int len = 2; len <= 30; len++) {
        cnt[len] = cnt[len - 1] + cnt[len - 2];
    }
    int ans = 0;
    for (int i = 30; i >= 0; i--) {
        if (i == 0) {
            ans++;
            break;
        }
        if ((n & (1 << i)) != 0) {
            ans += cnt[i];
            if ((n & (1 << (i + 1))) != 0) {
                break;
            }
        }
    }
    return ans;
}

int main()
{
    int n;
    scanf("%d",&n);
    printf("%d\n",findIntegers1(n));
    printf("%d\n",findIntegersIterative(n));
    return 0;
}
