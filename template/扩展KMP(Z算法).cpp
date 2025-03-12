// 扩展KMP模版，又称Z算法或Z函数
// 给定两个字符串a、b，求出两个数组
// b与b每一个后缀串的最长公共前缀长度，z数组
// b与a每一个后缀串的最长公共前缀长度，e数组
// 计算出要求的两个数组后，输出这两个数组的权值即可
// 对于一个数组x，i位置的权值定义为 : (i * (x[i] + 1))
// 数组权值为所有位置权值的异或和
// 测试链接 : https://www.luogu.com.cn/problem/P5410
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 20000001;

int z[MAXN];
int e[MAXN];
char a[MAXN];
char b[MAXN];
int n,m;

void zArray(char* s, int n) {
    z[0] = n;
    for (int i = 1, c = 1, r = 1, len; i < n; i++) {
        len = r > i ? min(r - i, z[i - c]) : 0;
        while (i + len < n && s[i + len] == s[len]) {
            len++;
        }
        if (i + len > r) {
            r = i + len;
            c = i;
        }
        z[i] = len;
    }
}

void eArray(char* a, char* b, int n, int m) {
    for (int i = 0, c = 0, r = 0, len; i < n; i++) {
        len = r > i ? min(r - i, z[i - c]) : 0;
        while (i + len < n && len < m && a[i + len] == b[len]) {
            len++;
        }
        if (i + len > r) {
            r = i + len;
            c = i;
        }
        e[i] = len;
    }
}
//如果说有参数的话直接就是模版

long eor(int* arr, int n) {
    long ans = 0;
    for (int i = 0; i < n; i++) {
        ans ^= (long) (i + 1) * (arr[i] + 1);
    }
    return ans;
}

int main()
{
    scanf("%s",a);
    n=strlen(a);
    scanf("%s",b);
    m=strlen(b);
    zArray(b,m);
    eArray(a,b,n,m);
    cout<<eor(z,m)<<endl;
    cout<<eor(e,n)<<endl;
    return 0;
}
