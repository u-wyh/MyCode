// 完全没有重复的数字个数
// 给定正整数n，返回在[1, n]范围内每一位都互不相同的正整数个数
// 测试链接 : https://leetcode.cn/problems/count-special-integers/
#include <stdio.h>
#include <stdlib.h>

int f(int *cnt, int num, int len, int offset, int status) {
    //len表示还有多少位没有填好
    //status表示状态（二进制）  表示哪些数字已经被选择过了
    if (len == 0) {
        return 1;
    }
    int first = (num / offset) % 10;
    //表示在这一位上的数字的值
    int ans = 0;
    for (int cur = 0; cur < first; cur++) {
        if ((status & (1 << cur)) == 0) {
            ans += cnt[len - 1];
        }
    }
    //表示选择还没有选并且比当前的值要小的数字  那么直接可以加上cnt中的值
    if ((status & (1 << first)) == 0) {
        ans += f(cnt, num, len - 1, offset / 10, status | (1 << first));
    }
    //表示选择当前的值
    return ans;
}

int countSpecialNumbers(int n) {
    int len = 1;
    int offset = 1;
    int tmp = n / 10;
    while (tmp > 0) {
        len++;
        offset *= 10;
        tmp /= 10;
    }
    //将len offset的值进行初始化
    int *cnt = (int *)malloc(sizeof(int) * len);
    if (cnt == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    // cnt[i] :
    // 一共长度为len，   还剩i位没有确定，确定的前缀为len-i位，      且确定的前缀不为空
    // 0~9一共10个数字，没有选择的数字剩下10-(len-i)个
    // 那么在后续的i位上，有多少种排列
    // 比如：len = 4
    // cnt[4]不计算
    // cnt[3] = 9 * 8 * 7
    // cnt[2] = 8 * 7
    // cnt[1] = 7
    // cnt[0] = 1，表示前缀已确定，后续也没有了，那么就是1种排列，就是前缀的状况
    // 再比如：len = 6
    // cnt[6]不计算
    // cnt[5] = 9 * 8 * 7 * 6 * 5
    // cnt[4] = 8 * 7 * 6 * 5
    // cnt[3] = 7 * 6 * 5
    // cnt[2] = 6 * 5
    // cnt[1] = 5
    // cnt[0] = 1，表示前缀已确定，后续也没有了，那么就是1种排列，就是前缀的状况
    // 下面for循环就是求解cnt的代码
    cnt[0] = 1;
    for (int i = 1, k = 10 - len + 1; i < len; i++, k++) {
        cnt[i] = cnt[i - 1] * k;
    }

    int ans = 0;
    if (len >= 2) {
        ans = 9;
        for (int i = 2, a = 9, b = 9; i < len; i++, b--) {
            a *= b;
            ans += a;//此时的ans是计算位数不足len的情况
        }
    }

    int first = n / offset;
    ans += (first - 1) * cnt[len - 1];
    //ans首先可以加上数位相同并且第一位也一样的
    ans += f(cnt, n, len - 1, offset / 10, 1 << first);

    free(cnt);
    return ans;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    printf("Number of special integers <= %d: %d\n", n, countSpecialNumbers(n));
    return 0;
}
