// 范围内的数字计数
// 给定两个正整数a和b，求在[a,b]范围上的所有整数中
// 每个数码(digit)各出现了多少次
// 1 <= a, b
// 测试链接 : https://www.luogu.com.cn/problem/P2602
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过

#include<bits/stdc++.h>
using namespace std;

long a,b;

long count(long num, int d) {
    long ans = 0;
    for (long right = 1, tmp = num, left, cur; tmp != 0; right *= 10, tmp /= 10) {
        left = tmp / 10;
        if (d == 0) {
            left--;
        }
        ans += left * right;
        cur = tmp % 10;
        if (cur > d) {
            ans += right;
        } else if (cur == d) {
            ans += num % right + 1;
        }
    }
    return ans;
}

int main()
{
    cin>>a>>b;
    for(int d=0;d<10;d++){
        cout<<(count(b,d)-count(a-1,d))<<' ';
    }
    return 0;
}
