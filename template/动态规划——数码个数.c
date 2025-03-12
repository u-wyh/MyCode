#include <stdio.h>
#include <stdlib.h>

long count(long num, int d) {
    long ans = 0;
    // 情况1：
    // d != 0
    // 1 ~ 30583 , d = 5
    // cur < d的情况
    // 个位cur=3 : 0000~3057 5
    // 个位上没有额外加
    //
    // cur > d的情况
    // 十位cur=8 : 000~304 5 0~9
    // 十位上额外加 : 305 5 0~9
    //
    // cur == d的情况
    // 百位cur=5 : 00~29 5 00~99
    // 百位上额外加 : 30 5 00~83
    // ...
    // 情况2：
    // d == 0
    // 1 ~ 30583 d = 0
    // cur > d的情况
    // 个位cur=3 : 0001~3057 0
    // 个位上额外加 : 3058 0
    //
    // cur > d的情况
    // 十位cur=8 : 001~304 0 0~9
    // 十位上额外加 : 305 0 0~9
    //
    // cur > d的情况
    // 百位cur=5 : 01~29 0 00~99
    // 百位上额外加 : 30 0 00~99
    //
    // cur == d的情况
    // 千位cur=0 : 1~2 0 000~099
    // 千位上额外加 : 3 0 000~583
    for (long right = 1, tmp = num, left, cur; tmp != 0; right *= 10, tmp /= 10) {
        left = tmp / 10;
        //left是这一位左边可以有的情况数  从0开始
        if (d == 0) {
            left--;
        }
        //如果d就是0   那么left从1开始
        ans += left * right;
        //ans首先是左边的情况种类和右边相乘
        cur = tmp % 10;
        //cur是当前位置上的数字
        if (cur > d) {
            ans += right;
            //如果cur大于d   那么左边情况要加上1  右边是从0  到right-1
        } else if (cur == d) {
            ans += num % right + 1;
            //如果cur等于d   那么就是把右边剩余的数字加上
        }
    }
    return ans;
}
//right的取值始终都是10 100 1000 10000 这样的数字

long digitsCount(int d, long a, long b) {
    return count(b, d) - count(a - 1, d);
}
//d的含义是数码d  0 1 2 3 4 5 6 7 8 9
//计算从a到b的所有数字的数码个数   相当于求从1到b的  减去从1到a的

int main() {
    long a, b;
    scanf("%ld %ld",&a,&b);
    for (int i = 0; i <= 9; i++) {
        printf("%ld ", digitsCount(i, a, b));
    }
    return 0;
}
