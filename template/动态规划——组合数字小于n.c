#include<stdio.h>

// offset是辅助变量，完全由len决定，只是为了方便提取num中某一位数字，不是关键变量
// 还剩下len位没有决定
// 如果之前的位已经确定比num小，那么free == 1，表示接下的数字可以自由选择
// 如果之前的位和num一样，那么free == 0，表示接下的数字不能大于num当前位的数字
// 如果之前的位没有使用过数字，fix == 0
// 如果之前的位已经使用过数字，fix == 1
// 返回最终<=num的可能性有多少种
int f1(int* digits, int num, int offset, int len, int free, int fix,int n) {
    if (len == 0) {
        return fix == 1 ? 1 : 0;
    }
    int ans = 0;
    // num在当前位的数字
    int cur = (num / offset) % 10;
    if (fix == 0) {
        // 之前从来没有选择过数字
        // 当前依然可以不要任何数字，累加后续的可能性
        ans += f1(digits, num, offset / 10, len - 1, 1, 0,n);
    }
    if (free == 0) {
        // 不能自由选择的情况
        for (int k=0;k<n;k++) {
            int i=digits[k];
            if (i < cur) {
                ans += f1(digits, num, offset / 10, len - 1, 1, 1, n);
            } else if (i == cur) {
                ans += f1(digits, num, offset / 10, len - 1, 0, 1, n);
            } else {
                // i > cur
                break;
            }
        }
    } else {
    // 可以自由选择的情况
        ans += n * f1(digits, num, offset / 10, len - 1, 1, 1, n);
    }
    return ans;
}

int f2(int* digits, int* cnt, int num, int offset, int len,int n) {
    if (len == 0) {
        // num自己
        return 1;
    }
    // cur是num当前位的数字
    int cur = (num / offset) % 10;
    int ans = 0;
    for (int k=0;k<n;k++) {
        int i=digits[k];
        if (i < cur) {
            ans += cnt[len - 1];
        } else if (i == cur) {
            ans += f2(digits, cnt, num, offset / 10, len - 1,n);
        } else {
            break;
        }
    }
    return ans;
}

int main()
{
    int n,num;
    scanf("%d %d",&n,&num);
    int nums[n];
    for(int i=0;i<n;i++)
    {
        scanf("%d",&nums[i]);
    }
    int tmp = num / 10;
    int len = 1;
    int offset = 1;
    while (tmp > 0) {
        tmp /= 10;
        len++;
        offset *= 10;
    }
    //len是计算位数的   offset是10的len次方
    //printf("%d %d\n",len,offset);
    printf("%d\n",f1(nums,num,offset,len,0,0,n));
    // cnt[i] : 已知前缀比num小，剩下i位没有确定，请问前缀确定的情况下，一共有多少种数字排列
    // cnt[0] = 1，表示后续已经没有了，前缀的状况都已确定，那么就是1种
    // cnt[1] = m
    // cnt[2] = m * m
    // cnt[3] = m * m * m
    // ...
    int cnt[len];
    cnt[0] = 1;
    int ans = 0;
    for (int i = n, k = 1; k < len; k++, i *= n) {
        cnt[k] = i;
        ans += i;//此时的ans是位数不足len的情况  f2是计算位数一样的情况
    }
    printf("%d\n", ans + f2(nums, cnt, num, offset, len, n));
    return 0;
}
