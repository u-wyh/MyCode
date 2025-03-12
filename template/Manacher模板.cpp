// Manacher算法模版
// 求字符串s中最长回文子串的长度
// 测试链接 : https://www.luogu.com.cn/problem/P3805
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 11000001;

char ss[MAXN << 1];//这个数组中间添加了#
char a[MAXN];//原始数组
int p[MAXN << 1];//半径数组
int n;

void manacherss() {
    n = strlen(a) * 2 + 1;
    for (int i = 0, j = 0; i < n; i++) {
        ss[i] = (i & 1) == 0 ? '#' : a[j++];
    }
}

int manacher() {
    manacherss();
    int maxans = 0;
    for (int i = 0, c = 0, r = 0, len; i < n; i++) {//i是此时来到的中心位置
        len = r > i ? min(p[2 * c - i], r - i) : 1;//这个值是基本值  如果包住了  那么基本值就是最终值  否则后续再加
        while (i + len < n && i - len >= 0 && ss[i + len] == ss[i - len]) {
            len++;
            //如果被包住了  那么直接跳出来了
        }
        //此时已经求出了以i为中心的回文半径大小
        if (i + len > r) {
            r = i + len;
            c = i;//c表示的是如今的r是以那个点为中心的右边界
            //如果更新了右边界  那么c就是i  r就是i+len
        }
        maxans = max(maxans, len);
        p[i] = len;
        //得到回文半径
    }
    return maxans - 1;
}

int main()
{
    scanf("%s",a);
    cout<<manacher();
    return 0;
}
